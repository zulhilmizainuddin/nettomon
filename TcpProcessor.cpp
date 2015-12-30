#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include "PacketPayload.h"
#include "TcpProcessor.h"


void TcpProcessor::process(string srcIp, string dstIp, const struct pcap_pkthdr *pkthdr, const u_char *packet,
                           vector<NetData> netData) {
    struct tcphdr* tcpHeader =
            (struct tcphdr*)(packet + sizeof(struct ether_header) + sizeof(struct ip));

    auto srcPort = ntohs(tcpHeader->source);
    auto dstPort = ntohs(tcpHeader->dest);

    for (auto data: netData) {
        struct in_addr localAddr;
        struct in_addr remoteAddr;

        localAddr.s_addr = stoul(data.localIp, NULL, 16);
        remoteAddr.s_addr = stoul(data.remoteIp, NULL, 16);

        string localIp = inet_ntoa(localAddr);
        string remoteIp = inet_ntoa(remoteAddr);

        auto localPort = stoul(data.localPort, NULL, 16);
        auto remotePort = stoul(data.remotePort, NULL, 16);

        if (srcIp == localIp && srcPort == localPort && dstIp == remoteIp && dstPort == remotePort) {
            PacketPayload::getInstance().addUploadedBytes(pkthdr->len);
            /*printf("%s:%d->%s:%d upload:%d\n", srcIp.c_str(), srcPort, dstIp.c_str(), dstPort, pkthdr->len);*/
            break;
        }

        if (srcIp == remoteIp && srcPort == remotePort && dstIp == localIp && dstPort == localPort) {
            PacketPayload::getInstance().addDownloadedBytes(pkthdr->len);
            /*printf("%s:%d->%s:%d download:%d\n", srcIp.c_str(), srcPort, dstIp.c_str(), dstPort, pkthdr->len);*/
            break;
        }
    }
}
