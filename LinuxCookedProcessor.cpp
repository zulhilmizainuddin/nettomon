#include <netinet/ether.h>
#include "sll.h"
#include "IPv4Processor.h"
#include "IPv6Processor.h"
#include "LinuxCookedProcessor.h"


void LinuxCookedProcessor::process(const struct pcap_pkthdr *pkthdr, const u_char *packet, const vector<NetData> &ipNetData,
                                   const vector<NetData> &ip6NetData) {

    struct sll_header* linuxCookedHeader = (struct sll_header*)packet;
    const u_char* ipHeader = packet + sizeof(sll_header);

    auto etherType = ntohs((uint16_t)linuxCookedHeader->sll_protocol);
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
