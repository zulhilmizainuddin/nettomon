#include <netinet/in.h>
#include "TcpProcessor.h"
#include "UdpProcessor.h"
#include "TransportLayerProcessorFactory.h"


unique_ptr<TransportLayerProcessor> TransportLayerProcessorFactory::getProcessor(int type) {
    switch (type) {
        case IPPROTO_TCP:
            return unique_ptr<TransportLayerProcessor>(new TcpProcessor);
        case IPPROTO_UDP:
            return unique_ptr<TransportLayerProcessor>(new UdpProcessor);
        default:
            return nullptr;
    }
}
