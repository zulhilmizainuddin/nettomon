#include <pcap.h>
#include <mutex>
#include "LinkLayerController.h"
#include "PcapDumper.h"
#include "InputValidation.h"
#include "Sniffer.h"


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

    pcap_t* packetDescriptor =
            pcap_open_live(deviceName.c_str(), DEFAULT_SNAPLEN, 0, 100, errbuf);

    if (packetDescriptor == nullptr) {
        perror("Failed to listen to device");
        exit(1);
    }

    data.datalink = pcap_datalink(packetDescriptor);

    PcapDumper::getInstance().openPcapDumpFile(
            packetDescriptor, InputValidation::getInstance().pcapDumpLocation);

    pcap_loop(packetDescriptor, -1, [](u_char* args, const struct pcap_pkthdr* pkthdr, const u_char* packet) {

        netDataMutex.lock();

        auto data = reinterpret_cast<struct Data*>(args);

        vector<NetData> tcpNetData(data->tcpNetData);
        vector<NetData> udpNetData(data->udpNetData);
        vector<NetData> tcp6NetData(data->tcp6NetData);
        vector<NetData> udp6NetData(data->udp6NetData);

        netDataMutex.unlock();

        LinkLayerController(data->datalink)
                .route(pkthdr,
                       packet,
                       tcpNetData,
                       udpNetData,
                       tcp6NetData,
                       udp6NetData
                );

    }, reinterpret_cast<u_char*>(&data));
}


void Sniffer::updateNetData(const vector<NetData> &tcpNetData, const vector<NetData> &udpNetData,
                            const vector<NetData> &tcp6NetData, const vector<NetData> &udp6NetData) {

    netDataMutex.lock();

    data.tcpNetData = move(tcpNetData);
    data.udpNetData = move(udpNetData);
    data.tcp6NetData = move(tcp6NetData);
    data.udp6NetData = move(udp6NetData);

    netDataMutex.unlock();
}