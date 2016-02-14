#include <net/ethernet.h>
#include "IPv4Processor.h"
#include "IPv6Processor.h"
#include "InternetLayerProcessorFactory.h"


unique_ptr<InternetLayerProcessor> InternetLayerProcessorFactory::getProcessor(int type) {
    switch (type) {
        case ETHERTYPE_IP:
            return unique_ptr<InternetLayerProcessor>(new IPv4Processor);
        case ETHERTYPE_IPV6:
            return unique_ptr<InternetLayerProcessor>(new IPv6Processor);
        default:
            return nullptr;
    }
}
