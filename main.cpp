#include <regex>
#include "ProcNetPublisher.h"
#include "Sniffer.h"
#include "ProcReadTimer.h"
#include "NetworkSpeedTimer.h"

using namespace std;

int main(int argc, char* argv[]) {

    if (argc != 2) {
        perror("Usage: nettomon pid");
        exit(1);
    }

    if (!regex_match(argv[1], regex("^[0-9]+$"))) {
        perror("pid must be an integer");
        exit(1);
    }

    auto procReadTimer = ProcReadTimer();
    auto sniffer = Sniffer(&procReadTimer);

    procReadTimer.start(argv[1]);
    NetworkSpeedTimer().start();

    sniffer.sniff(100);

    return 0;
}