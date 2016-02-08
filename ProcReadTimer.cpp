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
    unordered_map<string, NetData> tcp6InodeIp;
    unordered_map<string, NetData> udp6InodeIp;

    #pragma omp parallel sections
    {
        #pragma omp section
        socketsInode = ProcFd(pid).getSocketInodeList();

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

    vector<NetData> ipNetData;
    vector<NetData> ip6NetData;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            ipNetData.reserve(tcpNetData.size() + udpNetData.size());
            ipNetData.insert(ipNetData.end(), tcpNetData.begin(), tcpNetData.end());
            ipNetData.insert(ipNetData.end(), udpNetData.begin(), udpNetData.end());
        }

        #pragma omp section
        {
            ip6NetData.reserve(tcp6NetData.size() + udp6NetData.size());
            ip6NetData.insert(ip6NetData.end(), tcp6NetData.begin(), tcp6NetData.end());
            ip6NetData.insert(ip6NetData.end(), udp6NetData.begin(), udp6NetData.end());
        }
    }

    procNetPublisher->setNetData(ipNetData, ip6NetData);
    procNetPublisher->notifyObservers();

    duration.end();

    timer->expires_at(timer->expires_at() + posix_time::microseconds(500000 - duration.inMicroSeconds()));
    timer->async_wait(bind(procRead, asio::placeholders::error, timer, pid));
}