#include "LinkLayerProcessorFactory.h"
#include "LinkLayerController.h"


void LinkLayerController::route(const struct pcap_pkthdr *pkthdr, const u_char *packet, const vector<NetData> &tcpNetData,
                                const vector<NetData> &udpNetData, const vector<NetData> &tcp6NetData, const vector<NetData> &udp6NetData) {

    auto processor = LinkLayerProcessorFactory().getProcessor(datalink);
    if (processor != nullptr) {
        processor->process(pkthdr, packet, tcpNetData, udpNetData, tcp6NetData, udp6NetData);
    }
}
