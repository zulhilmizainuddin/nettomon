#ifndef NETTOMON_PROCFD_H
#define NETTOMON_PROCFD_H

#include <fstream>
#include <vector>

using namespace std;

class ProcFd {
private:
    string pid;
public:
    ProcFd(string pid) : pid(pid) { }

    vector<string> getSocketInodeList();

private:
    vector<string> retrieveSocketsInode();
    string extractSocketInode(string symlinkContent);
};


#endif //NETTOMON_PROCFD_H
