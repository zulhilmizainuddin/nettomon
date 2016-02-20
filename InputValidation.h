#ifndef NETTOMON_INPUTVALIDATION_H
#define NETTOMON_INPUTVALIDATION_H

#include <string>

using namespace std;

class InputValidation {
public:
    bool printListFormat = false;
    int runDuration = -1;
    string pcapDumpLocation = "";

public:
    static InputValidation & getInstance() {
        static InputValidation instance;
        return instance;
    }

    void validateNumberOfArguments(int argc);
    void validateHelp(string option);
    void validatePID(string &pid);
    void validateOptions(int argc, char **options);

private:
    InputValidation() { }
    InputValidation(InputValidation &);
    void operator=(InputValidation const&);
};


#endif //NETTOMON_INPUTVALIDATION_H
