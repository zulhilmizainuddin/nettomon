#include <pthread.h>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "PacketPayload.h"
#include "NetworkSpeedTimer.h"

using namespace std;
using namespace boost;

void *startDisplayNetworkSpeedTimer(void *argv);
void displayNetworkSpeed(const system::error_code &code, asio::deadline_timer *timer, int interval);

void NetworkSpeedTimer::start(int interval) {
    pthread_t thread;

    int threadStatus = pthread_create(&thread, NULL, startDisplayNetworkSpeedTimer, &interval);

    if  (threadStatus != 0) {
        perror("Failed to create network speed thread");
        exit(1);
    }

    if (pthread_detach(thread) != 0) {
        perror("Failed to detach network speed thread");
    }

}

void *startDisplayNetworkSpeedTimer(void *argv) {
    int interval = *(int*)argv;

    asio::io_service io;

    asio::deadline_timer timer(io, posix_time::milliseconds(interval));
    timer.async_wait(bind(displayNetworkSpeed, asio::placeholders::error, &timer, interval));

    io.run();
}

void displayNetworkSpeed(const system::error_code &code, asio::deadline_timer *timer, int interval) {

    printf("\rUpload: %7.1lf KB     Download: %7.1lf KB",
           PacketPayload::getInstance().getUploadedBytes() / (float)interval,
           PacketPayload::getInstance().getDownloadedBytes() / (float)interval);
    fflush(stdout);

    PacketPayload::getInstance().resetUploadedBytes();
    PacketPayload::getInstance().resetDownloadedBytes();

    timer->expires_at(timer->expires_at() + posix_time::milliseconds(interval));
    timer->async_wait(bind(displayNetworkSpeed, asio::placeholders::error, timer, interval));
}