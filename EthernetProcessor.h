#ifndef NETTOMON_ETHERNETPROCESSOR_H
#define NETTOMON_ETHERNETPROCESSOR_H


#include "PacketProcessor.h"

class EthernetProcessor : PacketProcessor {
public:
    virtual void process(const struct pcap_pkthdr *pkthdr, const u_char *packet, const vector<NetData> &netData);
};


#endif //NETTOMON_ETHERNETPROCESSOR_H
