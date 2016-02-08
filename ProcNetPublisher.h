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
    vector<NetData> ipNetData;
    vector<NetData> ip6NetData;

public:
    void setNetData(const vector<NetData> &ipNetData, const vector<NetData> &ip6NetData);
    void registerObserver(ProcNetObserver * observer);
    void notifyObservers();
};


#endif //NETTOMON_PROCPUBLISHER_H
