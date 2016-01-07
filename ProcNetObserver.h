#ifndef NETTOMON_PROCOBSERVER_H
#define NETTOMON_PROCOBSERVER_H

#include <vector>
#include "NetData.h"
#include "ProcNetPublisher.h"

class ProcNetPublisher;

class ProcNetObserver {
public:
    virtual ~ProcNetObserver() { }

    virtual void updateNetData(vector<NetData> tcpNetData, vector<NetData> udpNetData) = 0;

protected:
    ProcNetPublisher * procPublisher;
};


#endif //NETTOMON_PROCOBSERVER_H
