#ifndef NETTOMON_UDPPROCESSOR_H
#define NETTOMON_UDPPROCESSOR_H


#include <netinet/udp.h>
#include "TransportLayerProcessor.h"

class UdpProcessor : public TransportLayerProcessor {
public:
    virtual uint16_t getSourcePort(const u_char *header);
    virtual uint16_t getDestinationPort(const u_char *header);
};


#endif //NETTOMON_UDPPROCESSOR_H
