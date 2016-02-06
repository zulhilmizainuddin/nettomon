#include <netinet/ether.h>
#include <netinet/ip.h>
#include "sll.h"
#include "IPv4Processor.h"
#include "LinuxCookedProcessor.h"


void LinuxCookedProcessor::process(const struct pcap_pkthdr *pkthdr, const u_char *packet, const vector<NetData> &netData) {

    struct ip* ipHeader;
    struct sll_header* linuxCookedHeader = (struct sll_header*)packet;

    int etherType = ntohs(linuxCookedHeader->sll_protocol);
    switch (etherType) {
        case ETHERTYPE_IP:
            ipHeader = (struct ip*)(packet + SLL_HDR_LEN);
            IPv4Processor().process(ipHeader, pkthdr, netData);
            break;
        default:
            break;
    }
}
