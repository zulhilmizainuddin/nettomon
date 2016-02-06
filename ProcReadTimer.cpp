#include <thread>
#include <future>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "ProcFd.h"
#include "ProcNet.h"
#include "InodeIpHelper.h"
#include "ProcNetPublisher.h"
#include "Duration.h"
#include "ProcReadTimer.h"


using namespace std;
using namespace boost;

void procRead(const system::error_code &code, asio::deadline_timer *timer, const string& pid);

ProcNetPublisher* procNetPublisher;

ProcReadTimer::ProcReadTimer() {
    procNetPublisher = this;
}

void ProcReadTimer::start(const char *pid) {

    thread procReadThread([](const char* processId) {
        asio::io_service io;

        asio::deadline_timer timer(io, posix_time::microseconds(0));
        timer.async_wait(bind(procRead, asio::placeholders::error, &timer, processId));

        io.run();
    }, pid);

    procReadThread.detach();
}

void procRead(const system::error_code &code, asio::deadline_timer *timer, const string& pid) {

    Duration duration;
    duration.start();

    vector<string> socketsInode;
    unordered_map<string, NetData> tcpInodeIp;
    unordered_map<string, NetData> udpInodeIp;

    #pragma omp parallel sections
    {
        #pragma omp section
        socketsInode = ProcFd(pid).getSocketInodeList();

        #pragma omp section
        tcpInodeIp = ProcNet("tcp").getInodesIpMap();

        #pragma omp section
        udpInodeIp = ProcNet("udp").getInodesIpMap();
    }

    vector<NetData> tcpNetData;
    vector<NetData> udpNetData;

    #pragma omp parallel sections
    {
        #pragma omp section
        tcpNetData = InodeIpHelper::filterProccessIp(socketsInode, tcpInodeIp);

        #pragma omp section
        udpNetData = InodeIpHelper::filterProccessIp(socketsInode, udpInodeIp);
    }

    procNetPublisher->setNetData(tcpNetData, udpNetData);
    procNetPublisher->notifyObservers();

    duration.end();

    timer->expires_at(timer->expires_at() + posix_time::microseconds(500000 - duration.inMicroSeconds()));
    timer->async_wait(bind(procRead, asio::placeholders::error, timer, pid));
}