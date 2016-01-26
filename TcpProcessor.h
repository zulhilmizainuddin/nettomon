#ifndef NETTOMON_TCPPROCESSOR_H
#define NETTOMON_TCPPROCESSOR_H


#include "PacketProcessor.h"

class TcpProcessor : PacketProcessor {
public:
    virtual void process(const string& srcIp, const string& dstIp, const struct pcap_pkthdr *pkthdr, const u_char *packet,
                             const vector<NetData>& netData);
};


#endif //NETTOMON_TCPPROCESSOR_H
