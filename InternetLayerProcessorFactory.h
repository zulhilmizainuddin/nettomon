#ifndef NETTOMON_INTERNETLAYERPROCESSORFACTORY_H
#define NETTOMON_INTERNETLAYERPROCESSORFACTORY_H


#include <memory>
#include "InternetLayerProcessor.h"

class InternetLayerProcessorFactory {
public:
    unique_ptr<InternetLayerProcessor> getProcessor(int type);
};


#endif //NETTOMON_INTERNETLAYERPROCESSORFACTORY_H
