#ifndef NETTOMON_ETHERNETPROCESSOR_H
#define NETTOMON_ETHERNETPROCESSOR_H


#include "LinkLayerProcessor.h"

class EthernetProcessor : public LinkLayerProcessor {
public:
    virtual void process(const struct pcap_pkthdr *pkthdr, const u_char *packet, const vector<NetData> &tcpNetData,
                             const vector<NetData> &udpNetData, const vector<NetData> &tcp6NetData, const vector<NetData> &udp6NetData);
};


#endif //NETTOMON_ETHERNETPROCESSOR_H
