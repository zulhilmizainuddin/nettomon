#include <netinet/ip6.h>
#include <arpa/inet.h>
#include "PacketPayload.h"
#include "IPv6Processor.h"


void IPv6Processor::process(void *header, const struct pcap_pkthdr *pkthdr, const vector<NetData> &netData) {

    struct ip6_hdr* ip6Header = (struct ip6_hdr*)header;

    char srcIp6Buffer[INET6_ADDRSTRLEN];
    char dstIp6Buffer[INET6_ADDRSTRLEN];

    string srcIp6 = inet_ntop(AF_INET6, &ip6Header->ip6_src, srcIp6Buffer, INET6_ADDRSTRLEN);
    string dstIp6 = inet_ntop(AF_INET6, &ip6Header->ip6_dst, dstIp6Buffer, INET6_ADDRSTRLEN);

    for (auto data: netData) {
        auto localIp6Base10 = (uint32_t)stoul(data.localIp, NULL, 16);
        auto remoteIp6Base10 = (uint32_t)stoul(data.remoteIp, NULL, 16);

        char localIp6Buffer[INET6_ADDRSTRLEN];
        char remoteIp6Buffer[INET6_ADDRSTRLEN];

        string localIp6 = inet_ntop(AF_INET6, &localIp6Base10, localIp6Buffer, INET6_ADDRSTRLEN);
        string remoteIp6 = inet_ntop(AF_INET6, &remoteIp6Base10, remoteIp6Buffer, INET6_ADDRSTRLEN);

        if (srcIp6 == localIp6 && dstIp6 == remoteIp6) {
            PacketPayload::getInstance().addUploadedBytes(pkthdr->caplen);
            break;
        }

        if (srcIp6 == remoteIp6 && dstIp6 == localIp6) {
            PacketPayload::getInstance().addDownloadedBytes(pkthdr->caplen);
            break;
        }
    }
}
