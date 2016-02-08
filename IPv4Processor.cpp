#include <netinet/ip.h>
#include <arpa/inet.h>
#include "PacketPayload.h"
#include "IPv4Processor.h"


void IPv4Processor::process(void *header, const struct pcap_pkthdr *pkthdr, const vector<NetData> &netData) {

    struct ip* ipHeader = (struct ip*)header;

    char srcIpBuffer[INET_ADDRSTRLEN];
    char dstIpBuffer[INET_ADDRSTRLEN];

    string srcIp = inet_ntop(AF_INET, &ipHeader->ip_src, srcIpBuffer, INET_ADDRSTRLEN);
    string dstIp = inet_ntop(AF_INET, &ipHeader->ip_dst, dstIpBuffer, INET_ADDRSTRLEN);

    for (auto data: netData) {
        auto localIpBase10 = (uint32_t)stoul(data.localIp, NULL, 16);
        auto remoteIpBase10 = (uint32_t)stoul(data.remoteIp, NULL, 16);

        char localIpBuffer[INET_ADDRSTRLEN];
        char remoteIpBuffer[INET_ADDRSTRLEN];

        string localIp = inet_ntop(AF_INET, &localIpBase10, localIpBuffer, INET_ADDRSTRLEN);
        string remoteIp = inet_ntop(AF_INET, &remoteIpBase10, remoteIpBuffer, INET_ADDRSTRLEN);

        if (srcIp == localIp && dstIp == remoteIp) {
            PacketPayload::getInstance().addUploadedBytes(pkthdr->caplen);
            /*PacketPayload::getInstance().addUploadedBytes(ntohs(ipHeader->ip_len));*/
            break;
        }

        if (srcIp == remoteIp && dstIp == localIp) {
            PacketPayload::getInstance().addDownloadedBytes(pkthdr->caplen);
            /*PacketPayload::getInstance().addDownloadedBytes(ntohs(ipHeader->ip_len));*/
            break;
        }
    }
}
