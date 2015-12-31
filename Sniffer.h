#ifndef NETTOMON_SNIFFER_H
#define NETTOMON_SNIFFER_H

#include <string>
#include <vector>
#include "NetData.h"
#include "ProcNetObserver.h"

using namespace std;

class Sniffer : ProcNetObserver {
public:
    Sniffer(ProcNetPublisher *procPublisher);

    void sniff();
    virtual void updateNetData(vector<NetData> tcpNetData, vector<NetData> udpNetData);
};


#endif //NETTOMON_SNIFFER_H
