#ifndef NETTOMON_IPV4PROCESSOR_H
#define NETTOMON_IPV4PROCESSOR_H


#include "InternetLayerProcessor.h"

class IPv4Processor : InternetLayerProcessor {
public:
    virtual void process(struct ip *ipHeader, const struct pcap_pkthdr *pkthdr, const vector<NetData> &netData);
};


#endif //NETTOMON_IPV4PROCESSOR_H
