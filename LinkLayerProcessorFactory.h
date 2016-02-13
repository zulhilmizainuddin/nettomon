#ifndef NETTOMON_LINKLAYERPROCESSORFACTORY_H
#define NETTOMON_LINKLAYERPROCESSORFACTORY_H


#include "LinkLayerProcessor.h"

class LinkLayerProcessorFactory {
public:
    LinkLayerProcessor * getProcessor(int type);
};


#endif //NETTOMON_LINKLAYERPROCESSORFACTORY_H
