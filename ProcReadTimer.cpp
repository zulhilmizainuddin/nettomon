#include <thread>
#include <future>
#include <algorithm>
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

void procRead(const system::error_code &code, asio::deadline_timer *timer, const string &pid,
              const vector<string>& cachedSocketsInode);

ProcNetPublisher* procNetPublisher;

ProcReadTimer::ProcReadTimer() {
    procNetPublisher = this;
}

void ProcReadTimer::start(string pid) {

    thread procReadThread([](string processId) {
        asio::io_service io;

        asio::deadline_timer timer(io, posix_time::microseconds(0));
        timer.async_wait(bind(procRead, asio::placeholders::error, &timer, processId, vector<string>({""})));

        io.run();
    }, pid);

    procReadThread.detach();
}

void procRead(const system::error_code &code, asio::deadline_timer *timer, const string &pid,
              const vector<string>& cachedSocketsInode) {

    Duration duration;
    duration.start();

    vector<string> socketsInode;
    unordered_map<string, NetData> tcpInodeIp;
    unordered_map<string, NetData> udpInodeIp;
    unordered_map<string, NetData> tcp6InodeIp;
    unordered_map<string, NetData> udp6InodeIp;

    socketsInode = ProcFd(pid).getSocketInodeList();

    int matchCounter = 0;
    for (auto& cachedInode: cachedSocketsInode) {
        auto iter = find(socketsInode.begin(), socketsInode.end(), cachedInode);
        if (iter != socketsInode.end()) {
            ++matchCounter;
        }
    }

    if (matchCounter != cachedSocketsInode.size()) {

        #pragma omp parallel sections
        {
            #pragma omp section
            tcpInodeIp = ProcNet("tcp").getInodesIpMap();

            #pragma omp section
            udpInodeIp = ProcNet("udp").getInodesIpMap();

            #pragma omp section
            tcp6InodeIp = ProcNet("tcp6").getInodesIpMap();

            #pragma omp section
            udp6InodeIp = ProcNet("udp6").getInodesIpMap();
        }

        vector<NetData> tcpNetData;
        vector<NetData> udpNetData;
        vector<NetData> tcp6NetData;
        vector<NetData> udp6NetData;

        #pragma omp parallel sections
        {
            #pragma omp section
            tcpNetData = InodeIpHelper::filterProccessIp(socketsInode, tcpInodeIp);

            #pragma omp section
            udpNetData = InodeIpHelper::filterProccessIp(socketsInode, udpInodeIp);

            #pragma omp section
            tcp6NetData = InodeIpHelper::filterProccessIp(socketsInode, tcp6InodeIp);

            #pragma omp section
            udp6NetData = InodeIpHelper::filterProccessIp(socketsInode, udp6InodeIp);
        }

        procNetPublisher->setNetData(tcpNetData, udpNetData, tcp6NetData, udp6NetData);
        procNetPublisher->notifyObservers();
    }

    duration.end();

    timer->expires_at(timer->expires_at() + posix_time::microseconds(500000 - duration.inMicroSeconds()));
    timer->async_wait(bind(procRead, asio::placeholders::error, timer, pid, socketsInode));
}