#ifndef NETTOMON_TRANSPORTPROCESSOR_H
#define NETTOMON_TRANSPORTPROCESSOR_H

#include <vector>
#include <pcap/pcap.h>
#include "NetData.h"

class PacketProcessor {
public:
    virtual ~PacketProcessor() { }

    virtual void process(string srcIp, string dstIp, const struct pcap_pkthdr *pkthdr, const u_char *packet,
                             vector<NetData> netData) = 0;
};

#endif //NETTOMON_TRANSPORTPROCESSOR_H
