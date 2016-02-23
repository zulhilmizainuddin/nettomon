#include <netinet/in.h>
#include "UdpProcessor.h"


uint16_t UdpProcessor::getSourcePort(const u_char *header) {
    auto udpHeader = reinterpret_cast<const struct udphdr*>(header);

    return htons(static_cast<uint16_t>(udpHeader->source));
}

uint16_t UdpProcessor::getDestinationPort(const u_char *header) {
    auto udpHeader = reinterpret_cast<const struct udphdr*>(header);

    return htons(static_cast<uint16_t>(udpHeader->dest));
}
