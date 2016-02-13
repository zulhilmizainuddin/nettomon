#include <net/ethernet.h>
#include "IPv4Processor.h"
#include "IPv6Processor.h"
#include "InternetLayerProcessorFactory.h"


InternetLayerProcessor *InternetLayerProcessorFactory::getProcessor(int type) {
    InternetLayerProcessor* processor = NULL;

    switch (type) {
        case ETHERTYPE_IP:
            processor = new IPv4Processor;
            break;
        case ETHERTYPE_IPV6:
            processor = new IPv6Processor;
            break;
        default:
            break;
    }

    return processor;
}
