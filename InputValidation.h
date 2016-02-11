#ifndef NETTOMON_INPUTVALIDATION_H
#define NETTOMON_INPUTVALIDATION_H

#include <string>

using namespace std;

class InputValidation {
public:
    void ValidateNumberOfArguments(int argc);
    void ValidateHelp(string option);
    void ValidatePID(string &pid);
    void ValidateOptions(int argc, char *options[]);
};


#endif //NETTOMON_INPUTVALIDATION_H
