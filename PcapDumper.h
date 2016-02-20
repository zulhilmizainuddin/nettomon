#ifndef NETTOMON_PCAPDUMPER_H
#define NETTOMON_PCAPDUMPER_H


#include <pcap.h>
#include <string>

using namespace std;

class PcapDumper {
private:
    pcap_dumper_t* pcapDumpHandler = nullptr;

public:
    static PcapDumper & getInstance() {
        static PcapDumper instance;
        return instance;
    }

    void openPcapDumpFile(pcap_t *packetDescriptor, string filename);
    void writePcapToFile(const pcap_pkthdr *pkthdr, const u_char *packet);
    void closePcapDumpFile();

private:
    PcapDumper() { }
    PcapDumper(PcapDumper &);
    void operator=(PcapDumper const&);
};


#endif //NETTOMON_PCAPDUMPER_H
