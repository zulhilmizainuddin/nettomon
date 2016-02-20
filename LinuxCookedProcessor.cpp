#include <netinet/ether.h>
#include "sll.h"
#include "InternetLayerProcessorFactory.h"
#include "LinuxCookedProcessor.h"


void LinuxCookedProcessor::process(const struct pcap_pkthdr *pkthdr, const u_char *packet, const vector<NetData> &ipNetData,
                                   const vector<NetData> &ip6NetData) {

    const struct sll_header* linuxCookedHeader = reinterpret_cast<const struct sll_header*>(packet);
    const u_char* ipHeader = packet + sizeof(sll_header);

    vector<NetData> ipNetDataTemp;

    auto etherType = ntohs(static_cast<uint16_t>(linuxCookedHeader->sll_protocol));
    switch (etherType) {
        case ETHERTYPE_IP:
            ipNetDataTemp = move(ipNetData);
            break;
        case ETHERTYPE_IPV6:
            ipNetDataTemp = move(ip6NetData);
            break;
        default:
            return;
    }

    auto processor = InternetLayerProcessorFactory().getProcessor(etherType);
    if (processor != nullptr) {
        processor->process(ipHeader, pkthdr, packet, ipNetDataTemp);
    }
}
