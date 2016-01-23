#include <regex>
#include "ProcNetPublisher.h"
#include "Sniffer.h"
#include "ProcReadTimer.h"
#include "NetworkSpeedTimer.h"

using namespace std;

bool printListFormat = false;

int main(int argc, char* argv[]) {

    if (argc < 2) {
        perror("Usage: nettomon pid [OPTIONS]");
        exit(1);
    }

    if (!regex_match(argv[1], regex("^[0-9]{1,5}+$"))) {
        perror("pid must be an integer");
        exit(1);
    }

    if (argc > 2 && string(argv[2]) == "-l") {
        printListFormat = true;
    }

    auto procReadTimer = ProcReadTimer();
    auto sniffer = Sniffer(&procReadTimer);

    procReadTimer.start(argv[1]);
    NetworkSpeedTimer().start();

    sniffer.sniff();

    return 0;
}