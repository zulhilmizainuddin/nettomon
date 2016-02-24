#ifndef NETTOMON_IPV6PROCESSOR_H
#define NETTOMON_IPV6PROCESSOR_H


#include "InternetLayerProcessor.h"

class IPv6Processor : public InternetLayerProcessor {
public:
    virtual void process(const u_char *header, const struct pcap_pkthdr *pkthdr, const u_char *packet,
                             const vector<NetData> &tcpNetData, const vector<NetData> &udpNetData, const vector<NetData> &tcp6NetData,
                             const vector<NetData> &udp6NetData);

private:
    vector<NetData> prepareNetData(uint8_t protocol, const vector<NetData> &tcp6NetData,
                                   const vector<NetData> &udp6NetData);
};


#endif //NETTOMON_IPV6PROCESSOR_H
