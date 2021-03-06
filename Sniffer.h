#ifndef NETTOMON_SNIFFER_H
#define NETTOMON_SNIFFER_H

#include <string>
#include <vector>
#include "NetData.h"
#include "ProcNetObserver.h"

using namespace std;

class Sniffer : ProcNetObserver {
private:
    static const unsigned int DEFAULT_SNAPLEN = 262144;

    struct Data {
        int datalink;
        vector<NetData> tcpNetData;
        vector<NetData> udpNetData;
        vector<NetData> tcp6NetData;
        vector<NetData> udp6NetData;
    };

    struct Data data;

public:
    Sniffer(ProcNetPublisher *procPublisher);

    void sniff();
    virtual void updateNetData(const vector<NetData> &tcpNetData, const vector<NetData> &udpNetData,
                               const vector<NetData> &tcp6NetData, const vector<NetData> &udp6NetData);
};


#endif //NETTOMON_SNIFFER_H