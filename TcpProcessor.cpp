#include <netinet/in.h>
#include "TcpProcessor.h"


uint16_t TcpProcessor::getSourcePort(const u_char *header) {
    auto tcpHeader = reinterpret_cast<const struct tcphdr*>(header);

    return htons(static_cast<uint16_t>(tcpHeader->source));
}

uint16_t TcpProcessor::getDestinationPort(const u_char *header) {
    auto tcpHeader = reinterpret_cast<const struct tcphdr*>(header);

    return htons(static_cast<uint16_t>(tcpHeader->dest));
}

