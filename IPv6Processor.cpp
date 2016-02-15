#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <arpa/inet.h>
#include "PacketPayload.h"
#include "IPv6Processor.h"


void IPv6Processor::process(const u_char *header, const struct pcap_pkthdr *pkthdr, const vector<NetData> &netData) {

    const struct ip6_hdr* ip6Header = reinterpret_cast<const struct ip6_hdr*>(header);

    char srcIp6Buffer[INET6_ADDRSTRLEN];
    char dstIp6Buffer[INET6_ADDRSTRLEN];

    string srcIp6 = inet_ntop(AF_INET6, &ip6Header->ip6_src, srcIp6Buffer, INET6_ADDRSTRLEN);
    string dstIp6 = inet_ntop(AF_INET6, &ip6Header->ip6_dst, dstIp6Buffer, INET6_ADDRSTRLEN);

    for (auto data: netData) {
        struct in6_addr localIp6Addr;
        struct in6_addr remoteIp6Addr;

        char localIp6Buffer[INET6_ADDRSTRLEN];
        char remoteIp6Buffer[INET6_ADDRSTRLEN];

        sscanf(data.localIp.c_str(), "%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx",
               &localIp6Addr.s6_addr[3], &localIp6Addr.s6_addr[2], &localIp6Addr.s6_addr[1], &localIp6Addr.s6_addr[0],
               &localIp6Addr.s6_addr[7], &localIp6Addr.s6_addr[6], &localIp6Addr.s6_addr[5], &localIp6Addr.s6_addr[4],
               &localIp6Addr.s6_addr[11], &localIp6Addr.s6_addr[10], &localIp6Addr.s6_addr[9], &localIp6Addr.s6_addr[8],
               &localIp6Addr.s6_addr[15], &localIp6Addr.s6_addr[14], &localIp6Addr.s6_addr[13], &localIp6Addr.s6_addr[12]);

        sscanf(data.remoteIp.c_str(), "%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx",
               &remoteIp6Addr.s6_addr[3], &remoteIp6Addr.s6_addr[2], &remoteIp6Addr.s6_addr[1], &remoteIp6Addr.s6_addr[0],
               &remoteIp6Addr.s6_addr[7], &remoteIp6Addr.s6_addr[6], &remoteIp6Addr.s6_addr[5], &remoteIp6Addr.s6_addr[4],
               &remoteIp6Addr.s6_addr[11], &remoteIp6Addr.s6_addr[10], &remoteIp6Addr.s6_addr[9], &remoteIp6Addr.s6_addr[8],
               &remoteIp6Addr.s6_addr[15], &remoteIp6Addr.s6_addr[14], &remoteIp6Addr.s6_addr[13], &remoteIp6Addr.s6_addr[12]);

        string localIp6 = inet_ntop(AF_INET6, &localIp6Addr, localIp6Buffer, INET6_ADDRSTRLEN);
        string remoteIp6 = inet_ntop(AF_INET6, &remoteIp6Addr, remoteIp6Buffer, INET6_ADDRSTRLEN);

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
