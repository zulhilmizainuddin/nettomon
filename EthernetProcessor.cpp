#include <netinet/ether.h>
#include "InternetLayerProcessorFactory.h"
#include "EthernetProcessor.h"


void EthernetProcessor::process(const struct pcap_pkthdr *pkthdr, const u_char *packet, const vector<NetData> &ipNetData,
                                const vector<NetData> &ip6NetData) {

    const struct ether_header* etherHeader = reinterpret_cast<const struct ether_header*>(packet);
    const u_char* ipHeader = packet + sizeof(struct ether_header);

    vector<NetData> ipNetDataTemp;

    auto etherType = ntohs(static_cast<uint16_t>(etherHeader->ether_type));
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
        processor->process(ipHeader, pkthdr, ipNetDataTemp);
    }
}

