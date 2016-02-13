#ifndef NETTOMON_INTERNETLAYERPROCESSORFACTORY_H
#define NETTOMON_INTERNETLAYERPROCESSORFACTORY_H


#include "InternetLayerProcessor.h"

class InternetLayerProcessorFactory {
public:
    InternetLayerProcessor* getProcessor(int type);
};


#endif //NETTOMON_INTERNETLAYERPROCESSORFACTORY_H
