#ifndef NETTOMON_IPV4PROCESSOR_H
#define NETTOMON_IPV4PROCESSOR_H


#include "InternetLayerProcessor.h"

class IPv4Processor : public InternetLayerProcessor {
public:
    virtual void process(const u_char *header, const struct pcap_pkthdr *pkthdr, const u_char *packet,
                             const vector<NetData> &ipNetData, const vector<NetData> &ip6NetData);
};


#endif //NETTOMON_IPV4PROCESSOR_H
