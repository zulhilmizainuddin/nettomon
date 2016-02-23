#include <netinet/ether.h>
#include "sll.h"
#include "InternetLayerProcessorFactory.h"
#include "LinuxCookedProcessor.h"


void LinuxCookedProcessor::process(const struct pcap_pkthdr *pkthdr, const u_char *packet, const vector<NetData> &tcpNetData,
                                   const vector<NetData> &udpNetData, const vector<NetData> &tcp6NetData, const vector<NetData> &udp6NetData) {

    const struct sll_header* linuxCookedHeader = reinterpret_cast<const struct sll_header*>(packet);
    const u_char* ipHeader = packet + sizeof(struct sll_header);

    auto etherType = ntohs(static_cast<uint16_t>(linuxCookedHeader->sll_protocol));

    auto processor = InternetLayerProcessorFactory().getProcessor(etherType);
    if (processor != nullptr) {
        processor->process(ipHeader, pkthdr, packet, tcpNetData, udpNetData, tcp6NetData, udp6NetData);
    }
}
