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
public:
    Sniffer(ProcNetPublisher *procPublisher);

    void sniff();
    virtual void updateNetData(const vector<NetData> &ipNetData, const vector<NetData> &ip6NetData);
};


#endif //NETTOMON_SNIFFER_H