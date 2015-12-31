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

public:
    void setNetData(vector<NetData> tcpNetData, vector<NetData> udpNetData);
    void registerObserver(ProcNetObserver * observer);
    void notifyObservers();
};


#endif //NETTOMON_PROCPUBLISHER_H
