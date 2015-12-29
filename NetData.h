#ifndef NETTOMON_NETDATA_H
#define NETTOMON_NETDATA_H

#include <string>

using namespace std;

struct NetData {
    string localIp;
    string localPort;
    string remoteIp;
    string remotePort;
};

#endif //NETTOMON_NETDATA_H
