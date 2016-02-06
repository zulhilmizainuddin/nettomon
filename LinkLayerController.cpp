#include "EthernetProcessor.h"
#include "LinuxCookedProcessor.h"
#include "LinkLayerController.h"


void LinkLayerController::route(const struct pcap_pkthdr *pkthdr, const u_char *packet,
                                const vector<NetData> &netData) {

    switch (datalink) {
        case DLT_EN10MB:
            EthernetProcessor().process(pkthdr, packet, netData);
            break;
        case DLT_LINUX_SLL:
            LinuxCookedProcessor().process(pkthdr, packet, netData);
        default:
            return;
    }
}
