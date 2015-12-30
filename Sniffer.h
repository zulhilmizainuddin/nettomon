#ifndef NETTOMON_SNIFFER_H
#define NETTOMON_SNIFFER_H

#include <string>
#include <vector>
#include "NetData.h"

using namespace std;

class Sniffer {
public:
    Sniffer(const vector<NetData> &tcpNetData, const vector<NetData> &udpNetData);

    void sniff();

private:
    string retrieveListeningDeviceName();
};


#endif //NETTOMON_SNIFFER_H
