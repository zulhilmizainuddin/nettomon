#include <pthread.h>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "ProcFd.h"
#include "ProcNet.h"
#include "InodeIpHelper.h"
#include "ProcNetPublisher.h"
#include "ProcReadTimer.h"

void *startTimer(void *argv);
void procRead(const system::error_code &code, asio::deadline_timer *timer, string pid,
              ProcNetPublisher *procNetPublisher);

void *ProcReadTimer::start(ProcReadTimerData data) {
    pthread_t procReadThread;

    int timerThreadStatus = pthread_create(&procReadThread, NULL, startTimer, (void*)&data);

    if  (timerThreadStatus != 0) {
        perror("Failed to create proc read thread");
        exit(1);
    }
}

void *startTimer(void *argv) {
    struct ProcReadTimerData* procReadTimerData = (struct ProcReadTimerData*)argv;

    asio::io_service io;

    asio::deadline_timer procReadTimer(io, posix_time::milliseconds(500));
    procReadTimer.async_wait(bind(procRead, asio::placeholders::error, &procReadTimer, procReadTimerData->pid, procReadTimerData->publisher));

    io.run();
}

void procRead(const system::error_code &code, asio::deadline_timer *timer, string pid,
                             ProcNetPublisher *procNetPublisher) {
    auto socketsInode = ProcFd(pid).getSocketInodeList();

    auto tcpInodeIp = ProcNet("tcp").getInodesIpMap();
    auto udpInodeIp = ProcNet("udp").getInodesIpMap();

    auto tcpNetData = InodeIpHelper::filterProccessIp(socketsInode, tcpInodeIp);
    auto udpNetData = InodeIpHelper::filterProccessIp(socketsInode, udpInodeIp);

    procNetPublisher->setNetData(tcpNetData, udpNetData);
    procNetPublisher->notifyObservers();

    timer->expires_at(timer->expires_at() + posix_time::milliseconds(500));
    timer->async_wait(bind(procRead, asio::placeholders::error, timer, pid, procNetPublisher));
}
