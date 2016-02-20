#include <thread>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "PacketPayload.h"
#include "Duration.h"
#include "InputValidation.h"
#include "NetworkSpeedTimer.h"


using namespace std;
using namespace boost;

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

    string printSpeed("Tx: %8.1lf KB  |  Rx: %8.1lf KB");

    InputValidation::getInstance().printListFormat ?
            printSpeed = printSpeed + "\n" : printSpeed = "\r" + printSpeed;

    printf(printSpeed.c_str(),
           PacketPayload::getInstance().getUploadedBytes() / 1024.0,
           PacketPayload::getInstance().getDownloadedBytes() / 1024.0);
    fflush(stdout);

    PacketPayload::getInstance().resetUploadedBytes();
    PacketPayload::getInstance().resetDownloadedBytes();

    if (InputValidation::getInstance().runDuration != -1) {
        if (--InputValidation::getInstance().runDuration == 0) {
            exit(0);
        }
    }

    duration.end();

    timer->expires_at(timer->expires_at() + posix_time::microseconds(1000000 - duration.inMicroSeconds()));
    timer->async_wait(bind(displayNetworkSpeed, asio::placeholders::error, timer));
}