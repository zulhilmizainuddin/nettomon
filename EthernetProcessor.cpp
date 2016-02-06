#include <netinet/ether.h>
#include <netinet/ip.h>
#include "IPv4Processor.h"
#include "EthernetProcessor.h"


void EthernetProcessor::process(const struct pcap_pkthdr *pkthdr, const u_char *packet,
                                const vector<NetData> &netData) {

    struct ip* ipHeader;
    struct ether_header* etherHeader = (struct ether_header*)packet;

    int etherType = ntohs(etherHeader->ether_type);
    switch (etherType) {
        case ETHERTYPE_IP:
            ipHeader = (struct ip*)(packet + sizeof(struct ether_header));
            IPv4Processor().process(ipHeader, pkthdr, netData);
            break;
        default:
            break;
    }
}
