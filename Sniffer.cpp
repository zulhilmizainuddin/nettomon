#include <pcap.h>
#include <mutex>
#include "LinkLayerController.h"
#include "PcapDumper.h"
#include "InputValidation.h"
#include "Sniffer.h"

vector<NetData> tcpNetData;
vector<NetData> udpNetData;
vector<NetData> tcp6NetData;
vector<NetData> udp6NetData;

mutex netDataMutex;

int datalink = 0;

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

    pcap_t* packetDescriptor =
            pcap_open_live(deviceName.c_str(), DEFAULT_SNAPLEN, 0, 100, errbuf);

    if (packetDescriptor == nullptr) {
        perror("Failed to listen to device");
        exit(1);
    }

    datalink = pcap_datalink(packetDescriptor);

    PcapDumper::getInstance().openPcapDumpFile(
            packetDescriptor, InputValidation::getInstance().pcapDumpLocation);

    pcap_loop(packetDescriptor, -1, [](u_char* args, const struct pcap_pkthdr* pkthdr, const u_char* packet) {

        netDataMutex.lock();

        vector<NetData> tcpNetDataTemp(tcpNetData);
        vector<NetData> udpNetDataTemp(udpNetData);
        vector<NetData> tcp6NetDataTemp(tcp6NetData);
        vector<NetData> udp6NetDataTemp(udp6NetData);

        netDataMutex.unlock();

        LinkLayerController(datalink).route(pkthdr, packet, tcpNetDataTemp, udpNetDataTemp, tcp6NetDataTemp,
                                            udp6NetDataTemp);

    }, nullptr);
}


void Sniffer::updateNetData(const vector<NetData> &tcpNetData, const vector<NetData> &udpNetData,
                            const vector<NetData> &tcp6NetData, const vector<NetData> &udp6NetData) {
    netDataMutex.lock();

    ::tcpNetData = move(tcpNetData);
    ::udpNetData = move(udpNetData);
    ::tcp6NetData = move(tcp6NetData);
    ::udp6NetData = move(udp6NetData);

    netDataMutex.unlock();
}