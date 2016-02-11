#include <dirent.h>
#include <regex>
#include <fstream>
#include "ProcessId.h"

string ProcessId::getProcessId(const string &processName) {
    auto processId = retrieveProcessId(processName);

    return processId;
}

string ProcessId::retrieveProcessId(const string &processName) {
    string procDirectoryName = "/proc";

    DIR* procDirectory = opendir(procDirectoryName.c_str());
    if (procDirectory == NULL) {
        perror(string(procDirectoryName + " does not exist").c_str());
        exit(1);
    }

    string processId;
    while (struct dirent* processDirectory = readdir(procDirectory)) {
        if (regex_match(processDirectory->d_name, regex("^[0-9]{1,5}+$"))) {

            string filename = "/proc/" + string(processDirectory->d_name) + "/cmdline";

            ifstream file(filename);
            string store;

            getline(file, store);

            if (regex_match(store, regex(".*(?:" + processName + ")(?:\\x00)*+"))) {
                processId = processDirectory->d_name;
                break;
            }
        }
    }

    return processId;
}
