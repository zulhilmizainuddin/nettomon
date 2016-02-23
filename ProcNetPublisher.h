#ifndef NETTOMON_PROCPUBLISHER_H
#define NETTOMON_PROCPUBLISHER_H

#include <vector>
#include "NetData.h"
#include "ProcNetObserver.h"

using namespace std;

class ProcNetObserver;

class ProcNetPublisher {
private:
    vector<ProcNetObserver *> observers;
    vector<NetData> tcpNetData;
    vector<NetData> udpNetData;
    vector<NetData> tcp6NetData;
    vector<NetData> udp6NetData;

public:
    void setNetData(const vector<NetData> &tcpNetData, const vector<NetData> &udpNetData,
                        const vector<NetData> &tcp6NetData, const vector<NetData> &udp6NetData);
    void registerObserver(ProcNetObserver * observer);
    void notifyObservers();
};


#endif //NETTOMON_PROCPUBLISHER_H
