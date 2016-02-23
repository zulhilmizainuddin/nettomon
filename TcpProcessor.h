#ifndef NETTOMON_TCPPROCESSOR_H
#define NETTOMON_TCPPROCESSOR_H


#include <netinet/tcp.h>
#include "TransportLayerProcessor.h"

class TcpProcessor : public TransportLayerProcessor {
public:
    virtual uint16_t getSourcePort(const u_char *header);
    virtual uint16_t getDestinationPort(const u_char *header);
};


#endif //NETTOMON_TCPPROCESSOR_H
