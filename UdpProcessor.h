#ifndef NETTOMON_UDPPROCESSOR_H
#define NETTOMON_UDPPROCESSOR_H


#include "PacketProcessor.h"

class UdpProcessor : PacketProcessor {
public:
    virtual void process(string srcIp, string dstIp, const struct pcap_pkthdr *pkthdr, const u_char *packet,
                         vector<NetData> netData);
};


#endif //NETTOMON_UDPPROCESSOR_H
