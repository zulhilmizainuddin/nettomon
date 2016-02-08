#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include "IPv4Processor.h"
#include "IPv6Processor.h"
#include "EthernetProcessor.h"


void EthernetProcessor::process(const struct pcap_pkthdr *pkthdr, const u_char *packet, const vector<NetData> &ipNetData,
                                const vector<NetData> &ip6NetData) {

    struct ether_header* etherHeader = (struct ether_header*)packet;

    auto etherType = ntohs((uint16_t)etherHeader->ether_type);
    switch (etherType) {
        case ETHERTYPE_IP: {
            void* ipHeader = (struct ip*)(packet + sizeof(struct ether_header));
            IPv4Processor().process(ipHeader, pkthdr, ipNetData);
            break;
        }
        case ETHERTYPE_IPV6: {
            void* ip6Header = (struct ip6_hdr*)(packet + sizeof(struct ether_header));
            IPv6Processor().process(ip6Header, pkthdr, ip6NetData);
            break;
        }
        default:
            break;
    }
}

