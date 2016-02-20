#include <netinet/ip.h>
#include <arpa/inet.h>
#include "PacketPayload.h"
#include "PcapDumper.h"
#include "IPv4MappedIPv6.h"
#include "IPv4Processor.h"


void IPv4Processor::process(const u_char *header, const struct pcap_pkthdr *pkthdr, const u_char *packet,
                            const vector<NetData> &ipNetData, const vector<NetData> &ip6NetData) {

    const struct ip* ipHeader = reinterpret_cast<const struct ip*>(header);

    char srcIpBuffer[INET_ADDRSTRLEN];
    char dstIpBuffer[INET_ADDRSTRLEN];

    string srcIp = inet_ntop(AF_INET, &ipHeader->ip_src, srcIpBuffer, INET_ADDRSTRLEN);
    string dstIp = inet_ntop(AF_INET, &ipHeader->ip_dst, dstIpBuffer, INET_ADDRSTRLEN);

    vector<NetData> ipNetDataJoined;
    ipNetDataJoined.reserve(100);
    ipNetDataJoined = move(const_cast<vector<NetData>&>(ipNetData));

    for (auto data: ip6NetData) {
        struct NetData netData = move(IPv4MappedIPv6().extractIPv4NetData(data));
        if (!netData.localIp.empty()) {
            ipNetDataJoined.push_back(move(netData));
        }
    }

    for (auto data: ipNetDataJoined) {
        struct in_addr localIpAddr;
        struct in_addr remoteIpAddr;

        localIpAddr.s_addr = static_cast<uint32_t>(stoul(data.localIp, nullptr, 16));
        remoteIpAddr.s_addr = static_cast<uint32_t>(stoul(data.remoteIp, nullptr, 16));

        char localIpBuffer[INET_ADDRSTRLEN];
        char remoteIpBuffer[INET_ADDRSTRLEN];

        string localIp = inet_ntop(AF_INET, &localIpAddr, localIpBuffer, INET_ADDRSTRLEN);
        string remoteIp = inet_ntop(AF_INET, &remoteIpAddr, remoteIpBuffer, INET_ADDRSTRLEN);

        if (srcIp == localIp && dstIp == remoteIp) {
            PacketPayload::getInstance().addUploadedBytes(pkthdr->caplen);
            PcapDumper::getInstance().writePcapToFile(pkthdr, packet);
            /*PacketPayload::getInstance().addUploadedBytes(ntohs(ipHeader->ip_len));*/
            break;
        }

        if (srcIp == remoteIp && dstIp == localIp) {
            PacketPayload::getInstance().addDownloadedBytes(pkthdr->caplen);
            PcapDumper::getInstance().writePcapToFile(pkthdr, packet);
            /*PacketPayload::getInstance().addDownloadedBytes(ntohs(ipHeader->ip_len));*/
            break;
        }
    }
}
