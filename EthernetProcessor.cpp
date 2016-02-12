#include <netinet/ether.h>
#include "IPv4Processor.h"
#include "IPv6Processor.h"
#include "EthernetProcessor.h"


void EthernetProcessor::process(const struct pcap_pkthdr *pkthdr, const u_char *packet, const vector<NetData> &ipNetData,
                                const vector<NetData> &ip6NetData) {

    struct ether_header* etherHeader = (struct ether_header*)packet;
    const u_char* ipHeader = packet + sizeof(struct ether_header);

    auto etherType = ntohs((uint16_t)etherHeader->ether_type);
    switch (etherType) {
        case ETHERTYPE_IP:
            IPv4Processor().process(ipHeader, pkthdr, ipNetData);
            break;
        case ETHERTYPE_IPV6:
            IPv6Processor().process(ipHeader, pkthdr, ip6NetData);
            break;
        default:
            break;
    }
}

