#include <pthread.h>
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

    asio::deadline_timer timer(io, posix_time::milliseconds(100));
    timer.async_wait(bind(procRead, asio::placeholders::error, &timer, pid));

    io.run();
}

void procRead(const system::error_code &code, asio::deadline_timer *timer, string pid) {
    auto socketsInode = ProcFd(pid).getSocketInodeList();

    auto tcpInodeIp = ProcNet("tcp").getInodesIpMap();
    auto udpInodeIp = ProcNet("udp").getInodesIpMap();

    auto tcpNetData = InodeIpHelper::filterProccessIp(socketsInode, tcpInodeIp);
    auto udpNetData = InodeIpHelper::filterProccessIp(socketsInode, udpInodeIp);

    procNetPublisher->setNetData(tcpNetData, udpNetData);
    procNetPublisher->notifyObservers();

    timer->expires_at(timer->expires_at() + posix_time::milliseconds(100));
    timer->async_wait(bind(procRead, asio::placeholders::error, timer, pid));
}
