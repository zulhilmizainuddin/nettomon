#include <pcap.h>
#include <mutex>
#include "LinkLayerController.h"
#include "Sniffer.h"


vector<NetData> tcpNetData;
vector<NetData> udpNetData;

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

    if (packetDescriptor == NULL) {
        perror("Failed to listen to device");
        exit(1);
    }

    datalink = pcap_datalink(packetDescriptor);

    pcap_loop(packetDescriptor, -1, [](u_char* args, const struct pcap_pkthdr* pkthdr, const u_char* packet) {

        netDataMutex.lock();

        vector<NetData> netDataList;
        netDataList.reserve(tcpNetData.size() + udpNetData.size());
        netDataList.insert(netDataList.end(), tcpNetData.begin(), tcpNetData.end());
        netDataList.insert(netDataList.end(), udpNetData.begin(), udpNetData.end());

        netDataMutex.unlock();

        LinkLayerController(datalink).route(pkthdr, packet, netDataList);

    }, NULL);
}


void Sniffer::updateNetData(const vector<NetData>& tcpNetData, const vector<NetData>& udpNetData) {
    netDataMutex.lock();
    ::tcpNetData = tcpNetData;
    ::udpNetData = udpNetData;
    netDataMutex.unlock();
}