#include <netinet/ip.h>
#include <arpa/inet.h>
#include "PacketPayload.h"
#include "PcapDumper.h"
#include "IPv4MappedIPv6.h"
#include "TransportLayerProcessorFactory.h"
#include "IPv4Processor.h"


void IPv4Processor::process(const u_char *header, const struct pcap_pkthdr *pkthdr, const u_char *packet,
                            const vector<NetData> &tcpNetData, const vector<NetData> &udpNetData, const vector<NetData> &tcp6NetData,
                            const vector<NetData> &udp6NetData) {

    const struct ip* ipHeader = reinterpret_cast<const struct ip*>(header);

    char srcIpBuffer[INET_ADDRSTRLEN];
    char dstIpBuffer[INET_ADDRSTRLEN];

    string srcIp = inet_ntop(AF_INET, &ipHeader->ip_src, srcIpBuffer, INET_ADDRSTRLEN);
    string dstIp = inet_ntop(AF_INET, &ipHeader->ip_dst, dstIpBuffer, INET_ADDRSTRLEN);

    auto protocol = ipHeader->ip_p;
    auto processor = TransportLayerProcessorFactory().getProcessor(protocol);
    if (processor != nullptr) {
        auto srcPort = processor->getSourcePort(header + sizeof(struct ip));
        auto dstPort = processor->getDestinationPort(header + sizeof(struct ip));

        auto ipNetData = move(prepareNetData(protocol, tcpNetData, udpNetData, tcp6NetData, udp6NetData));
        for (auto& data: ipNetData) {
            struct in_addr localIpAddr;

            localIpAddr.s_addr = static_cast<uint32_t>(stoul(data.localIp, nullptr, 16));

            char localIpBuffer[INET_ADDRSTRLEN];

            string localIp = inet_ntop(AF_INET, &localIpAddr, localIpBuffer, INET_ADDRSTRLEN);
            uint32_t localPort = static_cast<uint32_t >(stoul(data.localPort, nullptr, 16));

            if (srcIp == localIp && srcPort == localPort) {
                PacketPayload::getInstance().addUploadedBytes(pkthdr->caplen);
                PcapDumper::getInstance().writePcapToFile(pkthdr, packet);
                break;
            }

            if (dstIp == localIp && dstPort == localPort) {
                PacketPayload::getInstance().addDownloadedBytes(pkthdr->caplen);
                PcapDumper::getInstance().writePcapToFile(pkthdr, packet);
                break;
            }
        }
    }
}

vector<NetData> IPv4Processor::prepareNetData(u_int8_t protocol, const vector<NetData> &tcpNetData,
                                               const vector<NetData> &udpNetData, const vector<NetData> &tcp6NetData,
                                               const vector<NetData> &udp6NetData) {
    vector<NetData> netDataJoined;
    netDataJoined.reserve(100);

    vector<NetData> ip6NetData;

    switch (protocol) {
        case IPPROTO_TCP:
            netDataJoined = move(const_cast<vector<NetData>&>(tcpNetData));
            ip6NetData = move(tcp6NetData);
            break;
        case IPPROTO_UDP:
            netDataJoined = move(const_cast<vector<NetData>&>(udpNetData));
            ip6NetData = move(udp6NetData);
            break;
        default:
            break;
    }

    for (auto& data: ip6NetData) {
        struct NetData netData = move(IPv4MappedIPv6().extractIPv4NetData(data));
        if (!netData.localIp.empty()) {
            netDataJoined.push_back(move(netData));
        }
    }

    return netDataJoined;
}
