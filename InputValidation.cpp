#include "InputValidation.h"

#include <regex>

bool printListFormat = false;
int runDuration = -1;

void InputValidation::ValidateNumberOfArguments(int argc) {
    if (argc < 2) {
        perror("Usage: nettomon pid [OPTIONS...]");
        exit(1);
    }
}

void InputValidation::ValidateHelp(string option) {
    if (string(option) == "-h") {
        printf("Usage: nettomon pid [OPTIONS...]\n\n");
        printf("  -l\t\t\tlist result line by line\n");
        printf("  -d n\t\t\texecute program for n number of seconds\n");
        exit(0);
    }
}

void InputValidation::ValidatePID(string pid) {
    if (!regex_match(pid, regex("^[0-9]{1,5}+$"))) {
        perror("pid must be an integer");
        exit(1);
    }
}

void InputValidation::ValidateOptions(int argc, char *options[]) {
    for (int i = 2; i < argc; ++i) {
        if (string(options[i]) == "-l") {
            printListFormat = true;
            continue;
        }

        if (string(options[i]) == "-d") {
            if ((i + 1) < argc && regex_match(options[++i], regex("^[0-9]++$"))) {
                runDuration = stoi(options[i], NULL, 10);
                continue;
            }
            else {
                perror("Option -d must be followed an integer");
                exit(1);
            }
        }
    }
}
