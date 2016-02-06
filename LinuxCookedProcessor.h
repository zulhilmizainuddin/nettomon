#ifndef NETTOMON_LINUXCOOKEDPROCESSOR_H
#define NETTOMON_LINUXCOOKEDPROCESSOR_H


#include "PacketProcessor.h"

class LinuxCookedProcessor : PacketProcessor {
public:
    virtual void process(const struct pcap_pkthdr *pkthdr, const u_char *packet, const vector<NetData> &netData);
};


#endif //NETTOMON_LINUXCOOKEDPROCESSOR_H
