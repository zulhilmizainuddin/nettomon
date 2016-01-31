#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include "PacketPayload.h"
#include "TcpProcessor.h"


void TcpProcessor::process(const string& srcIp, const string& dstIp, const struct pcap_pkthdr *pkthdr, const u_char *packet,
                           const vector<NetData>& netData) {
    struct tcphdr* tcpHeader =
            (struct tcphdr*)(packet + sizeof(struct ether_header) + sizeof(struct ip));

    auto srcPort = ntohs(tcpHeader->source);
    auto dstPort = ntohs(tcpHeader->dest);

    #pragma omp parallel for
    for (int i = 0; i < netData.size(); ++i) {
        struct in_addr localAddr;
        struct in_addr remoteAddr;

        localAddr.s_addr = stoul(netData[i].localIp, NULL, 16);
        remoteAddr.s_addr = stoul(netData[i].remoteIp, NULL, 16);

        string localIp = inet_ntoa(localAddr);
        string remoteIp = inet_ntoa(remoteAddr);

        auto localPort = stoul(netData[i].localPort, NULL, 16);
        auto remotePort = stoul(netData[i].remotePort, NULL, 16);

        if (srcIp == localIp && srcPort == localPort && dstIp == remoteIp && dstPort == remotePort) {
            PacketPayload::getInstance().addUploadedBytes(pkthdr->len);
        }

        if (srcIp == remoteIp && srcPort == remotePort && dstIp == localIp && dstPort == localPort) {
            PacketPayload::getInstance().addDownloadedBytes(pkthdr->len);
        }
    }
}
