#ifndef NETTOMON_PROCFD_H
#define NETTOMON_PROCFD_H

#include <fstream>
#include <vector>
#include <dirent.h>

using namespace std;

class ProcFd {
private:
    string pid;
public:
    ProcFd(string pid) : pid(pid) { }

    vector<string> getSocketsInode();

private:
    vector<string> getSymlinksContent();
    vector<string> extractSocketInodes(vector<string> symlinksContent);
};


#endif //NETTOMON_PROCFD_H
