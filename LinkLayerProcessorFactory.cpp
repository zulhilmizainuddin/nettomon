#include "EthernetProcessor.h"
#include "LinuxCookedProcessor.h"
#include "LinkLayerProcessorFactory.h"


unique_ptr<LinkLayerProcessor> LinkLayerProcessorFactory::getProcessor(int type) {
    switch (type) {
        case DLT_EN10MB:
            return unique_ptr<LinkLayerProcessor>(new EthernetProcessor);
        case DLT_LINUX_SLL:
            return unique_ptr<LinkLayerProcessor>(new LinuxCookedProcessor);
        default:
            return nullptr;
    }
}
