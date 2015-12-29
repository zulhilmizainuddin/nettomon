#ifndef NETTOMON_PROCNET_H
#define NETTOMON_PROCNET_H

#include <string>
#include <map>
#include <vector>
#include "NetData.h"

using namespace std;

class ProcNet {
private:
    string ipType;

public:
    ProcNet(string ipType) : ipType(ipType) { }

    map<string, NetData> getInodesIpMap();

private:
    vector<string> getIpTypeData();
    map<string, NetData> extractInodesIpMapping(vector<string> ipTypeDataList);
};


#endif //NETTOMON_PROCNET_H
