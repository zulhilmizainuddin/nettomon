#include "EthernetProcessor.h"
#include "LinuxCookedProcessor.h"
#include "LinkLayerProcessorFactory.h"


LinkLayerProcessor * LinkLayerProcessorFactory::getProcessor(int type) {
    LinkLayerProcessor*processor = NULL;

    switch (type) {
        case DLT_EN10MB:
            processor = new EthernetProcessor;
            break;
        case DLT_LINUX_SLL:
            processor = new LinuxCookedProcessor;
            break;
        default:
            break;
    }

    return processor;
}
