#ifndef NETTOMON_INODEIPHELPER_H
#define NETTOMON_INODEIPHELPER_H

#include <string>
#include <vector>
#include <map>
#include "NetData.h"

using namespace std;

class InodeIpHelper {
public:
    static map<string, NetData> join(map<string, NetData> tcp, map<string, NetData> udp);
    static map<string, NetData> filter(vector<string> socketInodes, map<string, NetData> inodeIps);
};


#endif //NETTOMON_INODEIPHELPER_H
