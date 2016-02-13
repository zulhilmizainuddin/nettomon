#include "LinkLayerProcessorFactory.h"
#include "LinkLayerController.h"


void LinkLayerController::route(const struct pcap_pkthdr *pkthdr, const u_char *packet, const vector<NetData> &ipNetData,
                                const vector<NetData> &ip6NetData) {

    auto processor = LinkLayerProcessorFactory().getProcessor(datalink);
    if (processor != NULL) {
        processor->process(pkthdr, packet, ipNetData, ip6NetData);

        delete processor;
    }
}
