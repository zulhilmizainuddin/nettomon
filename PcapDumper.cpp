#include <signal.h>
#include "PcapDumper.h"


void PcapDumper::openPcapDumpFile(pcap_t *packetDescriptor, string filename) {

    if (!filename.empty()) {
        pcapDumpHandler = pcap_dump_open(packetDescriptor, filename.c_str());
        if (pcapDumpHandler == nullptr) {
            perror(string("Failed to open " + filename + " pcap dump file").c_str());
            exit(1);
        }
    }

    signal(SIGINT, [](int signal) {
        PcapDumper::getInstance().closePcapDumpFile();
        exit(0);
    });
}

void PcapDumper::writePcapToFile(const pcap_pkthdr *pkthdr, const u_char *packet) {
    if (pcapDumpHandler != nullptr) {
        pcap_dump(reinterpret_cast<u_char*>(pcapDumpHandler), pkthdr, packet);
    }
}

void PcapDumper::closePcapDumpFile() {
    if (pcapDumpHandler != nullptr) {
        pcap_dump_close(pcapDumpHandler);
    }
}
