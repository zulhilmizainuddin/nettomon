#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include "sll.h"
#include "IPv4Processor.h"
#include "IPv6Processor.h"
#include "LinuxCookedProcessor.h"


void LinuxCookedProcessor::process(const struct pcap_pkthdr *pkthdr, const u_char *packet, const vector<NetData> &ipNetData,
                                   const vector<NetData> &ip6NetData) {

    struct sll_header* linuxCookedHeader = (struct sll_header*)packet;

    auto etherType = ntohs((uint16_t)linuxCookedHeader->sll_protocol);
    switch (etherType) {
        case ETHERTYPE_IP: {
            void* ipHeader = (struct ip*)(packet + sizeof(sll_header));
            IPv4Processor().process(ipHeader, pkthdr, ipNetData);
            break;
        }
        case ETHERTYPE_IPV6: {
            void* ip6Header = (struct ip6_hdr*)(packet + sizeof(sll_header));
            IPv6Processor().process(ip6Header, pkthdr, ip6NetData);
            break;
        }
        default:
            break;
    }
}
