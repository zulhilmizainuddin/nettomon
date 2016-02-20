#include <regex>
#include "ProcNetPublisher.h"
#include "Sniffer.h"
#include "ProcReadTimer.h"
#include "NetworkSpeedTimer.h"
#include "InputValidation.h"

using namespace std;

int main(int argc, char* argv[]) {

    string pid(argv[1]);

    InputValidation::getInstance().validateNumberOfArguments(argc);
    InputValidation::getInstance().validateHelp(argv[1]);
    InputValidation::getInstance().validatePID(pid);
    InputValidation::getInstance().validateOptions(argc, argv);

    auto procReadTimer = ProcReadTimer();
    auto sniffer = Sniffer(&procReadTimer);

    procReadTimer.start(pid);
    NetworkSpeedTimer().start();

    sniffer.sniff();

    return 0;
}