#include <pcap.h>
#include <arpa/inet.h>
#include <netinet/ether.h>
#include <netinet/ip.h>
#include <mutex>
#include "TcpProcessor.h"
#include "UdpProcessor.h"
#include "Sniffer.h"

vector<NetData> tcpNetData;
vector<NetData> udpNetData;

mutex netDataMutex;

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

    pcap_t* packetDescriptor = pcap_open_live(deviceName.c_str(), BUFSIZ, 0, 10, errbuf);

    if (packetDescriptor == NULL) {
        perror("Failed to listen to device");
        exit(1);
    }

    pcap_loop(packetDescriptor, -1, [](u_char* args, const struct pcap_pkthdr* pkthdr, const u_char* packet) {
        struct ip* ipHeader = (struct ip*)(packet + sizeof(struct ether_header));

        string srcIp = inet_ntoa(ipHeader->ip_src);
        string dstIp = inet_ntoa(ipHeader->ip_dst);

        switch (ipHeader->ip_p) {
            case IPPROTO_TCP: {
                netDataMutex.lock();
                auto tcpNetDataTemp(tcpNetData);
                netDataMutex.unlock();

                #pragma omp sections nowait
                {
                    #pragma omp section
                    TcpProcessor().process(srcIp, dstIp, pkthdr, packet, tcpNetDataTemp);
                }
                break;
            }
            case IPPROTO_UDP: {
                netDataMutex.lock();
                auto udpNetDataTemp(udpNetData);
                netDataMutex.unlock();

                #pragma omp sections nowait
                {
                    #pragma omp section
                    UdpProcessor().process(srcIp, dstIp, pkthdr, packet, udpNetDataTemp);
                }
                break;
            }
            default:
                return;
        }

    }, NULL);
}


void Sniffer::updateNetData(const vector<NetData>& tcpNetData, const vector<NetData>& udpNetData) {
    netDataMutex.lock();
    ::tcpNetData = tcpNetData;
    ::udpNetData = udpNetData;
    netDataMutex.unlock();
}