#ifndef NETTOMON_ETHERNETPROCESSOR_H
#define NETTOMON_ETHERNETPROCESSOR_H


#include "LinkLayerProcessor.h"

class EthernetProcessor : public LinkLayerProcessor {
public:
    virtual void process(const struct pcap_pkthdr *pkthdr, const u_char *packet, const vector<NetData> &ipNetData,
                             const vector<NetData> &ip6NetData);
};


#endif //NETTOMON_ETHERNETPROCESSOR_H
