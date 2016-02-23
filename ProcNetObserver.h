#ifndef NETTOMON_PROCOBSERVER_H
#define NETTOMON_PROCOBSERVER_H

#include <vector>
#include "NetData.h"
#include "ProcNetPublisher.h"

class ProcNetPublisher;

class ProcNetObserver {
public:
    virtual ~ProcNetObserver() { }

    virtual void updateNetData(const vector<NetData> &tcpNetData, const vector<NetData> &udpNetData,
                                   const vector<NetData> &tcp6NetData, const vector<NetData> &udp6NetData) = 0;

protected:
    ProcNetPublisher * procPublisher;
};


#endif //NETTOMON_PROCOBSERVER_H
