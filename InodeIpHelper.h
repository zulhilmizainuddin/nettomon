#ifndef NETTOMON_INODEIPHELPER_H
#define NETTOMON_INODEIPHELPER_H

#include <string>
#include <vector>
#include <map>
#include "NetData.h"

using namespace std;

class InodeIpHelper {
public:
    static vector<NetData> filterProccessIp(vector<string> socketInodes, map<string, NetData> inodeIps);
};


#endif //NETTOMON_INODEIPHELPER_H
