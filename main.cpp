#include <regex>
#include "ProcNetPublisher.h"
#include "Sniffer.h"
#include "ProcReadTimer.h"
#include "NetworkSpeedTimer.h"

using namespace std;

bool printListFormat = false;
int runDuration = -1;

int main(int argc, char* argv[]) {

    if (argc < 2) {
        perror("Usage: nettomon pid [OPTIONS]");
        exit(1);
    }

    if (!regex_match(argv[1], regex("^[0-9]{1,5}+$"))) {
        perror("pid must be an integer");
        exit(1);
    }

    for (int i = 2; i < argc; ++i) {
        if (string(argv[i]) == "-l") {
            printListFormat = true;
            continue;
        }

        if (string(argv[i]) == "-d") {
            if ((i + 1) < argc && regex_match(argv[++i], regex("^[0-9]++$"))) {
                runDuration = stoi(argv[i], NULL, 10);
                continue;
            }
            else {
                perror("Option -d must be followed an integer");
                exit(1);
            }
        }
    }

    auto procReadTimer = ProcReadTimer();
    auto sniffer = Sniffer(&procReadTimer);

    procReadTimer.start(argv[1]);
    NetworkSpeedTimer().start();

    sniffer.sniff();

    return 0;
}