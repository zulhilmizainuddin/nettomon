#include <netinet/ether.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include "PacketPayload.h"
#include "IPv4Processor.h"


void IPv4Processor::process(struct ip *ipHeader, const struct pcap_pkthdr *pkthdr, const vector<NetData> &netData) {

    string srcIp = inet_ntoa(ipHeader->ip_src);
    string dstIp = inet_ntoa(ipHeader->ip_dst);

    for (auto data: netData) {
        struct in_addr localAddr;
        struct in_addr remoteAddr;

        localAddr.s_addr = (uint32_t)stoul(data.localIp, NULL, 16);
        remoteAddr.s_addr = (uint32_t)stoul(data.remoteIp, NULL, 16);

        string localIp = inet_ntoa(localAddr);
        string remoteIp = inet_ntoa(remoteAddr);

        if (srcIp == localIp && dstIp == remoteIp) {
            PacketPayload::getInstance().addUploadedBytes(ntohs(ipHeader->ip_len));
            /*PacketPayload::getInstance().addUploadedBytes(pkthdr->caplen);*/
            break;
        }

        if (srcIp == remoteIp && dstIp == localIp) {
            PacketPayload::getInstance().addDownloadedBytes(ntohs(ipHeader->ip_len));
            /*PacketPayload::getInstance().addDownloadedBytes(pkthdr->caplen);*/
            break;
        }
    }
}
