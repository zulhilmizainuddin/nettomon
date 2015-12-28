#ifndef NETTOMON_PROCNET_H
#define NETTOMON_PROCNET_H

#include <string>
#include <map>
#include <vector>

using namespace std;

struct NetData {
    string localIp;
    string localPort;
    string remoteIp;
    string remotePort;
};

class ProcNet {
private:
    string ipType;

public:
    ProcNet(string ipType) : ipType(ipType) { }

    vector<map<string, NetData>> getInodesIpMapList();

private:
    vector<string> getIpTypeData();
    vector<map<string, NetData>> extractInodesIpMapping(vector<string> ipTypeDataList);
};


#endif //NETTOMON_PROCNET_H
