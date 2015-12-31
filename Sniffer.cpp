#include <pcap/pcap.h>
#include <arpa/inet.h>
#include <netinet/ether.h>
#include <netinet/ip.h>
#include <iostream>
#include "TcpProcessor.h"
#include "UdpProcessor.h"
#include "Sniffer.h"

vector<NetData> tcpNetData;
vector<NetData> udpNetData;

Sniffer::Sniffer(ProcNetPublisher *procPublisher) {
    this->procPublisher = procPublisher;
    this->procPublisher->registerObserver(this);
}

void Sniffer::sniff() {
    char errbuf[PCAP_ERRBUF_SIZE];

    string deviceName = pcap_lookupdev(errbuf);

    if (deviceName.empty()) {
        perror("Failed to get device to sniff on");
        exit(1);
    }

    pcap_t* packetDescriptor = pcap_open_live(deviceName.c_str(), BUFSIZ, 0, -1, errbuf);

    if (packetDescriptor == NULL) {
        perror("Failed to listen to device");
        exit(1);
    }

    pcap_loop(packetDescriptor, -1, [](u_char* args, const struct pcap_pkthdr* pkthdr, const u_char* packet) {
        struct ip* ipHeader = (struct ip*)(packet + sizeof(struct ether_header));

        string srcIp = inet_ntoa(ipHeader->ip_src);
        string dstIp = inet_ntoa(ipHeader->ip_dst);

        switch (ipHeader->ip_p) {
            case IPPROTO_TCP:
                TcpProcessor().process(srcIp, dstIp, pkthdr, packet, tcpNetData);
                break;
            case IPPROTO_UDP:
                UdpProcessor().process(srcIp, dstIp, pkthdr, packet, udpNetData);
                break;
            default:
                return;
        }

    }, NULL);
}


void Sniffer::updateNetData(vector<NetData> tcpNetData, vector<NetData> udpNetData) {
    ::tcpNetData = tcpNetData;
    ::udpNetData = udpNetData;
}
