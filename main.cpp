#include "ProcNetPublisher.h"
#include "Sniffer.h"
#include "ProcReadTimer.h"
#include "NetworkSpeedTimer.h"

using namespace std;

int main(int argc, char* argv[]) {

    if  (argc != 2) {
        perror("Usage: nettomon pid");
        exit(1);
    }

    string pid(argv[1]);
    for (int i = 0; i < pid.length(); ++i) {
        if (!isdigit(pid[i])) {
            perror("pid must be an integer");
            exit(1);
        }
    }

    auto procReadTimer = ProcReadTimer();
    Sniffer sniffer = Sniffer(&procReadTimer);

    procReadTimer.start(pid.c_str());
    NetworkSpeedTimer().start();

    sniffer.sniff();

    return 0;
}