#ifndef NETTOMON_PROCFD_H
#define NETTOMON_PROCFD_H

#include <fstream>
#include <vector>
#include <dirent.h>

using namespace std;

class ProcFd {
private:
    const char* pid;
public:
    ProcFd(const char *pid) : pid(pid) { }

    vector<const char *> getSocketsInode();

public:
    vector<const char *> getSymlinksContent();
    vector<const char *> extractSocketInodes(vector<const char *> symlinksContent);
};


#endif //NETTOMON_PROCFD_H
