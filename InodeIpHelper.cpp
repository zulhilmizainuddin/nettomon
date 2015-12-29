#include "InodeIpHelper.h"

map<string, NetData> InodeIpHelper::join(map<string, NetData> tcp, map<string, NetData> udp) {
    map<string, NetData> tcpUdpInodeIp;

    tcpUdpInodeIp.insert(tcp.begin(), tcp.end());
    tcpUdpInodeIp.insert(udp.begin(), udp.end());

    return tcpUdpInodeIp;
}

map<string, NetData> InodeIpHelper::filter(vector<string> socketInodes, map<string, NetData> inodeIps) {
    map<string, NetData> filteredResult;

    for (auto socketInode: socketInodes) {
        for (auto inodeIp: inodeIps) {
            if (socketInode == inodeIp.first) {
                filteredResult.insert(inodeIp);
                break;
            }
        }
    }

    return filteredResult;
}
