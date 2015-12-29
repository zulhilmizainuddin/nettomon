#include <pcap/pcap.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <net/if.h>
#include "Sniffer.h"

string Sniffer::getLocalIpv4() {
    char error[PCAP_ERRBUF_SIZE];
    char* deviceName = pcap_lookupdev(error);

    if (deviceName == NULL) {
        perror("Failed to get device to sniff on");
        exit(1);
    }

    bpf_u_int32 networkAddress;
    bpf_u_int32 subnetMask;

    int returnValue = pcap_lookupnet(deviceName, &networkAddress, &subnetMask, error);

    if (returnValue == -1) {
        perror("Failed to get network address/subnet mask");
        exit(1);
    }

    int socketFd = socket(AF_INET, SOCK_DGRAM, 0);

    struct ifreq ifr;
    ifr.ifr_addr.sa_family = AF_INET;

    strncpy(ifr.ifr_name, deviceName, IFNAMSIZ - 1);

    ioctl(socketFd, SIOCGIFADDR, &ifr);
    close(socketFd);

    string localIp = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);

    return localIp;
}