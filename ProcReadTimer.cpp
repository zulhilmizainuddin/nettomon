#include <thread>
#include <future>
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

void procRead(const system::error_code &code, asio::deadline_timer *timer, string pid);

ProcNetPublisher* procNetPublisher;

ProcReadTimer::ProcReadTimer() {
    procNetPublisher = this;
}

void ProcReadTimer::start(const char *pid) {

    thread procReadThread([](const char* processId) {
        asio::io_service io;

        asio::deadline_timer timer(io, posix_time::milliseconds(0));
        timer.async_wait(bind(procRead, asio::placeholders::error, &timer, processId));

        io.run();
    }, pid);

    procReadThread.detach();
}

void procRead(const system::error_code &code, asio::deadline_timer *timer, string pid) {

    ProcFd procFd(pid);
    auto socketsInodeFuture = async(&ProcFd::getSocketInodeList, &procFd);

    ProcNet procNetTcp("tcp");
    auto tcpInodeIpFuture = async(&ProcNet::getInodesIpMap, &procNetTcp);

    ProcNet procNetUdp("udp");
    auto udpInodeIpFuture = async(&ProcNet::getInodesIpMap, &procNetUdp);

    auto socketsInode = socketsInodeFuture.get();
    auto tcpInodeIp = tcpInodeIpFuture.get();
    auto udpInodeIp = udpInodeIpFuture.get();

    auto tcpNetDataFuture = async(&InodeIpHelper::filterProccessIp, socketsInode, tcpInodeIp);
    auto udpNetDataFuture = async(&InodeIpHelper::filterProccessIp, socketsInode, udpInodeIp);

    auto tcpNetData = tcpNetDataFuture.get();
    auto udpNetData = udpNetDataFuture.get();

    procNetPublisher->setNetData(tcpNetData, udpNetData);
    procNetPublisher->notifyObservers();

    timer->expires_at(timer->expires_at() + posix_time::milliseconds(500));
    timer->async_wait(bind(procRead, asio::placeholders::error, timer, pid));
}