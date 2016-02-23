#ifndef NETTOMON_LINKLAYERCONTROLLER_H
#define NETTOMON_LINKLAYERCONTROLLER_H

#include <vector>
#include <pcap.h>
#include "NetData.h"

class LinkLayerController {
private:
    int datalink;
public:
    LinkLayerController(int datalink) : datalink(datalink) { }

    void route(const struct pcap_pkthdr *pkthdr, const u_char *packet, const vector<NetData> &tcpNetData,
                   const vector<NetData> &udpNetData, const vector<NetData> &tcp6NetData, const vector<NetData> &udp6NetData);
};


#endif //NETTOMON_LINKLAYERCONTROLLER_H
