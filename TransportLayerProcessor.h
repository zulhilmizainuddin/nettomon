#ifndef NETTOMON_TRANSPORTLAYERPROCESSOR_H
#define NETTOMON_TRANSPORTLAYERPROCESSOR_H


#include <stdint.h>
#include <sys/types.h>

class TransportLayerProcessor {
public:
    virtual ~TransportLayerProcessor() { }

    virtual uint16_t getSourcePort(const u_char *header) = 0;
    virtual uint16_t getDestinationPort(const u_char *header) = 0;
};

#endif //NETTOMON_TRANSPORTLAYERPROCESSOR_H
