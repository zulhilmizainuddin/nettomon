#ifndef NETTOMON_INODEIPHELPER_H
#define NETTOMON_INODEIPHELPER_H

#include <string>
#include <vector>
#include <unordered_map>
#include "NetData.h"

using namespace std;

class InodeIpHelper {
public:
    static vector<NetData> filterProccessIp(vector<string> socketInodes, unordered_map<string, NetData> inodeIps);
};


#endif //NETTOMON_INODEIPHELPER_H
