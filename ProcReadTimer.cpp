#include <pthread.h>
#include <thread>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "ProcFd.h"
#include "ProcNet.h"
#include "InodeIpHelper.h"
#include "ProcNetPublisher.h"
#include "ProcReadTimer.h"


using namespace std;
using namespace boost;

void *startProcReadTimer(void *argv);
void procRead(const system::error_code &code, asio::deadline_timer *timer, string pid);

ProcNetPublisher* procNetPublisher;

ProcReadTimer::ProcReadTimer() {
    procNetPublisher = this;
}

void ProcReadTimer::start(const char *pid) {
    pthread_t thread;

    int threadStatus = pthread_create(&thread, NULL, startProcReadTimer, (void*)pid);

    if  (threadStatus != 0) {
        perror("Failed to create proc read thread");
        exit(1);
    }

    if (pthread_detach(thread) != 0) {
        perror("Failed to detach proc read thread");
    }

}

void *startProcReadTimer(void *argv) {
    string pid = (const char*)argv;

    asio::io_service io;

    asio::deadline_timer timer(io, posix_time::milliseconds(0));
    timer.async_wait(bind(procRead, asio::placeholders::error, &timer, pid));

    io.run();
}

void procRead(const system::error_code &code, asio::deadline_timer *timer, string pid) {

    vector<string> socketsInode;
    thread socketInodeThread([&socketsInode](string processId) {
        socketsInode = ProcFd(processId).getSocketInodeList();
    }, pid);

    unordered_map<string, NetData> tcpInodeIp;
    thread tcpInodeIpThread([&tcpInodeIp](string ipType) {
        tcpInodeIp = ProcNet(ipType).getInodesIpMap();
    }, "tcp");

    unordered_map<string, NetData> udpInodeIp;
    thread udpInodeIpThread([&udpInodeIp](string ipType) {
        udpInodeIp = ProcNet(ipType).getInodesIpMap();
    }, "udp");

    socketInodeThread.join();
    tcpInodeIpThread.join();
    udpInodeIpThread.join();

    vector<NetData> tcpNetData;
    thread tcpNetDataThread([&tcpNetData](vector<string> socketInodes, unordered_map<string, NetData> inodeIps) {
        tcpNetData = InodeIpHelper().filterProccessIp(socketInodes, inodeIps);
    }, socketsInode, tcpInodeIp);

    vector<NetData> udpNetData;
    thread udpNetDataThread([&udpNetData](vector<string> socketInodes, unordered_map<string, NetData> inodeIps) {
        udpNetData = InodeIpHelper().filterProccessIp(socketInodes, inodeIps);
    }, socketsInode, udpInodeIp);

    tcpNetDataThread.join();
    udpNetDataThread.join();

    procNetPublisher->setNetData(tcpNetData, udpNetData);
    procNetPublisher->notifyObservers();

    timer->expires_at(timer->expires_at() + posix_time::milliseconds(500));
    timer->async_wait(bind(procRead, asio::placeholders::error, timer, pid));
}