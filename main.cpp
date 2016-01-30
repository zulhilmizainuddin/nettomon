#include <regex>
#include "ProcNetPublisher.h"
#include "Sniffer.h"
#include "ProcReadTimer.h"
#include "NetworkSpeedTimer.h"
#include "InputValidation.h"

using namespace std;

int main(int argc, char* argv[]) {

    auto validation = InputValidation();

    validation.ValidateNumberOfArguments(argc);
    validation.ValidateHelp(argv[1]);
    validation.ValidatePID(argv[1]);
    validation.ValidateOptions(argc, argv);

    auto procReadTimer = ProcReadTimer();
    auto sniffer = Sniffer(&procReadTimer);

    procReadTimer.start(argv[1]);
    NetworkSpeedTimer().start();

    sniffer.sniff();

    return 0;
}