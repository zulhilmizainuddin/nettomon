#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <arpa/inet.h>
#include "PacketPayload.h"
#include "PcapDumper.h"
#include "TransportLayerProcessorFactory.h"
#include "IPv6Processor.h"


void IPv6Processor::process(const u_char *header, const struct pcap_pkthdr *pkthdr, const u_char *packet,
                            const vector<NetData> &tcpNetData, const vector<NetData> &udpNetData, const vector<NetData> &tcp6NetData,
                            const vector<NetData> &udp6NetData) {

    const struct ip6_hdr* ip6Header = reinterpret_cast<const struct ip6_hdr*>(header);

    char srcIp6Buffer[INET6_ADDRSTRLEN];
    char dstIp6Buffer[INET6_ADDRSTRLEN];

    string srcIp6 = inet_ntop(AF_INET6, &ip6Header->ip6_src, srcIp6Buffer, INET6_ADDRSTRLEN);
    string dstIp6 = inet_ntop(AF_INET6, &ip6Header->ip6_dst, dstIp6Buffer, INET6_ADDRSTRLEN);

    auto protocol = ip6Header->ip6_ctlun.ip6_un1.ip6_un1_nxt;
    auto processor = TransportLayerProcessorFactory().getProcessor(protocol);
    if (processor != nullptr) {
        auto srcPort = processor->getSourcePort(header + sizeof(struct ip6_hdr));
        auto dstPort = processor->getDestinationPort(header + sizeof(struct ip6_hdr));

        vector<NetData> ip6NetDataTemp;

        if (protocol == IPPROTO_TCP) {
            ip6NetDataTemp = move(tcp6NetData);
        } else if (protocol == IPPROTO_UDP) {
            ip6NetDataTemp = move(udp6NetData);
        }

        for (auto data: ip6NetDataTemp) {
            struct in6_addr localIp6Addr;

            char localIp6Buffer[INET6_ADDRSTRLEN];

            sscanf(data.localIp.c_str(), "%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx",
                   &localIp6Addr.s6_addr[3], &localIp6Addr.s6_addr[2], &localIp6Addr.s6_addr[1], &localIp6Addr.s6_addr[0],
                   &localIp6Addr.s6_addr[7], &localIp6Addr.s6_addr[6], &localIp6Addr.s6_addr[5], &localIp6Addr.s6_addr[4],
                   &localIp6Addr.s6_addr[11], &localIp6Addr.s6_addr[10], &localIp6Addr.s6_addr[9], &localIp6Addr.s6_addr[8],
                   &localIp6Addr.s6_addr[15], &localIp6Addr.s6_addr[14], &localIp6Addr.s6_addr[13], &localIp6Addr.s6_addr[12]);

            string localIp6 = inet_ntop(AF_INET6, &localIp6Addr, localIp6Buffer, INET6_ADDRSTRLEN);
            uint32_t localPort = static_cast<uint32_t >(stoul(data.localPort, nullptr, 16));

            if (srcIp6 == localIp6 && srcPort == localPort) {
                PacketPayload::getInstance().addUploadedBytes(pkthdr->caplen);
                PcapDumper::getInstance().writePcapToFile(pkthdr, packet);
                break;
            }

            if (dstIp6 == localIp6 && dstPort == localPort) {
                PacketPayload::getInstance().addDownloadedBytes(pkthdr->caplen);
                PcapDumper::getInstance().writePcapToFile(pkthdr, packet);
                break;
            }
        }
    }
}
