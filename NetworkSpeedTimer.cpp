#include <thread>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "PacketPayload.h"
#include "Duration.h"
#include "NetworkSpeedTimer.h"

using namespace std;
using namespace boost;

extern bool printListFormat;
extern int runDuration;

void displayNetworkSpeed(const system::error_code &code, asio::deadline_timer *timer);

void NetworkSpeedTimer::start() {

    thread networkSpeedThread([]() {
        asio::io_service io;

        asio::deadline_timer timer(io, posix_time::microseconds(1000000));
        timer.async_wait(bind(displayNetworkSpeed, asio::placeholders::error, &timer));

        io.run();
    });

    networkSpeedThread.detach();
}

void displayNetworkSpeed(const system::error_code &code, asio::deadline_timer *timer) {

    Duration duration;
    duration.start();

    string printSpeed("Upload: %7.1lf KB     Download: %7.1lf KB");

    printListFormat ?
            printSpeed = printSpeed + "\n" : printSpeed = "\r" + printSpeed;

    printf(printSpeed.c_str(),
           PacketPayload::getInstance().getUploadedBytes() / 1024.0,
           PacketPayload::getInstance().getDownloadedBytes() / 1024.0);
    fflush(stdout);

    PacketPayload::getInstance().resetUploadedBytes();
    PacketPayload::getInstance().resetDownloadedBytes();

    if (runDuration != -1) {
        if (--runDuration == 0) {
            exit(0);
        }
    }

    duration.end();

    timer->expires_at(timer->expires_at() + posix_time::microseconds(1000000 - duration.inMicroSeconds()));
    timer->async_wait(bind(displayNetworkSpeed, asio::placeholders::error, timer));
}