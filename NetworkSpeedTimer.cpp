#include <pthread.h>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "PacketPayload.h"
#include "NetworkSpeedTimer.h"

using namespace std;
using namespace boost;

void *startDisplayNetworkSpeedTimer(void *argv);
void displayNetworkSpeed(const system::error_code &code, asio::deadline_timer *timer);

void *NetworkSpeedTimer::start() {
    pthread_t thread;

    int threadStatus = pthread_create(&thread, NULL, startDisplayNetworkSpeedTimer, NULL);

    if  (threadStatus != 0) {
        perror("Failed to create network speed thread");
        exit(1);
    }
}

void *startDisplayNetworkSpeedTimer(void *argv) {
    asio::io_service io;

    asio::deadline_timer timer(io, posix_time::milliseconds(1000));
    timer.async_wait(bind(displayNetworkSpeed, asio::placeholders::error, &timer));

    io.run();
}

void displayNetworkSpeed(const system::error_code &code, asio::deadline_timer *timer) {

    printf("Upload: %7.1lf KB     Download: %7.1lf KB\n",
           PacketPayload::getInstance().getUploadedBytes() / 1000.0,
           PacketPayload::getInstance().getDownloadedBytes() / 1000.0);

    PacketPayload::getInstance().resetUploadedBytes();
    PacketPayload::getInstance().resetDownloadedBytes();

    timer->expires_at(timer->expires_at() + posix_time::milliseconds(1000));
    timer->async_wait(bind(displayNetworkSpeed, asio::placeholders::error, timer));
}