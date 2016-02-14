#ifndef NETTOMON_LINKLAYERPROCESSORFACTORY_H
#define NETTOMON_LINKLAYERPROCESSORFACTORY_H


#include <memory>
#include "LinkLayerProcessor.h"

class LinkLayerProcessorFactory {
public:
    unique_ptr<LinkLayerProcessor> getProcessor(int type);
};


#endif //NETTOMON_LINKLAYERPROCESSORFACTORY_H
