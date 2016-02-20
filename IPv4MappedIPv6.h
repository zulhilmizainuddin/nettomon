#ifndef NETTOMON_IPV4MAPPEDIPV6_H
#define NETTOMON_IPV4MAPPEDIPV6_H


#include <string>
#include "NetData.h"

using namespace std;

class IPv4MappedIPv6 {
public:
    NetData extractIPv4NetData(const NetData &ip6NetData);
};


#endif //NETTOMON_IPV4MAPPEDIPV6_H
