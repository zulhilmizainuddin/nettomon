#ifndef NETTOMON_PROCESSID_H
#define NETTOMON_PROCESSID_H


#include <string>

using namespace std;

class ProcessId {
public:
    string getProcessId(const string &processName);

private:
    string retrieveProcessId(const string &processName);
};


#endif //NETTOMON_PROCESSID_H
