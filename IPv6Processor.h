#ifndef NETTOMON_IPV6PROCESSOR_H
#define NETTOMON_IPV6PROCESSOR_H


#include "InternetLayerProcessor.h"

class IPv6Processor : public InternetLayerProcessor {
public:
    virtual void process(const u_char *header, const struct pcap_pkthdr *pkthdr, const u_char *packet,
                             const vector<NetData> &ipNetData, const vector<NetData> &ip6NetData);
};


#endif //NETTOMON_IPV6PROCESSOR_H
