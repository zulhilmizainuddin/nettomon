#ifndef NETTOMON_LINUXCOOKEDPROCESSOR_H
#define NETTOMON_LINUXCOOKEDPROCESSOR_H


#include "LinkLayerProcessor.h"

class LinuxCookedProcessor : public LinkLayerProcessor {
public:
    virtual void process(const struct pcap_pkthdr *pkthdr, const u_char *packet, const vector<NetData> &ipNetData,
                             const vector<NetData> &ip6NetData);
};


#endif //NETTOMON_LINUXCOOKEDPROCESSOR_H
