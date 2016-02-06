#ifndef NETTOMON_INTERNETLAYERPROCESSOR_H
#define NETTOMON_INTERNETLAYERPROCESSOR_H

#include <pcap.h>
#include <vector>
#include <netinet/ip.h>
#include "NetData.h"

class InternetLayerProcessor {
public:
    virtual ~InternetLayerProcessor() { }

    virtual void process(struct ip *ipHeader, const struct pcap_pkthdr *pkthdr, const vector<NetData> &netData) = 0;
};

#endif //NETTOMON_INTERNETLAYERPROCESSOR_H
