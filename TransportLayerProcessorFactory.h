#ifndef NETTOMON_TRANSPORTLAYERPROCESSORFACTORY_H
#define NETTOMON_TRANSPORTLAYERPROCESSORFACTORY_H


#include <memory>
#include "TransportLayerProcessor.h"

using namespace std;

class TransportLayerProcessorFactory {
public:
    unique_ptr<TransportLayerProcessor> getProcessor(int type);
};


#endif //NETTOMON_TRANSPORTLAYERPROCESSORFACTORY_H
