#include <regex>
#include "ProcessId.h"
#include "InputValidation.h"


void InputValidation::validateNumberOfArguments(int argc) {
    if (argc < 2) {
        perror("Usage: nettomon <pid | process name> [OPTIONS...]");
        exit(1);
    }
}

void InputValidation::validateHelp(string option) {
    if (string(option) == "-h") {
        printf("Usage: nettomon <pid | process name> [OPTIONS...]\n\n");
        printf("  -l\t\t\tlist result line by line\n");
        printf("  -d n\t\t\texecute program for n number of seconds\n");
        printf("  -w file\t\t\tdump captured packets into pcap format at file location\n");
        exit(0);
    }
}

void InputValidation::validatePID(string &pid) {
    if (!regex_match(pid, regex("^[0-9]{1,5}+$"))) {
        string processId = ProcessId().getProcessId(pid);

        if (processId.empty()) {
            perror("Entered pid/process does not exist");
            exit(1);
        }
        else {
            pid = processId;
        }
    }
}

void InputValidation::validateOptions(int argc, char **options) {
    for (int i = 2; i < argc; ++i) {
        if (string(options[i]) == "-l") {
            printListFormat = true;
            continue;
        }

        if (string(options[i]) == "-d") {
            if ((i + 1) < argc && regex_match(options[++i], regex("^[0-9]++$"))) {
                runDuration = stoi(options[i], nullptr, 10);
                continue;
            }
            else {
                perror("Option -d must be followed by an integer");
                exit(1);
            }
        }

        if (string(options[i]) == "-w") {
            if ((i + 1) < argc) {
                pcapDumpLocation = options[++i];
                continue;
            }
            else {
                perror("Option -w must be followed by a valid pcap dump location");
                exit(1);
            }
        }
    }
}
