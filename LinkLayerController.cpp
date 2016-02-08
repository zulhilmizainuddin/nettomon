#include "EthernetProcessor.h"
#include "LinuxCookedProcessor.h"
#include "LinkLayerController.h"


void LinkLayerController::route(const struct pcap_pkthdr *pkthdr, const u_char *packet, const vector<NetData> &ipNetData,
                                const vector<NetData> &ip6NetData) {

    switch (datalink) {
        case DLT_EN10MB:
            EthernetProcessor().process(pkthdr, packet, ipNetData, ip6NetData);
            break;
        case DLT_LINUX_SLL:
            LinuxCookedProcessor().process(pkthdr, packet, ipNetData, ip6NetData);
        default:
            return;
    }
}
