#ifndef NETTOMON_LINKLAYERPROCESSOR_H
#define NETTOMON_LINKLAYERPROCESSOR_H

#include <vector>
#include <pcap.h>
#include "NetData.h"

class LinkLayerProcessor {
public:
    virtual ~LinkLayerProcessor() { }

    virtual void process(const struct pcap_pkthdr *pkthdr, const u_char *packet, const vector<NetData> &ipNetData,
                             const vector<NetData> &ip6NetData) = 0;
};

#endif //NETTOMON_LINKLAYERPROCESSOR_H
