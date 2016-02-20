#include <regex>
#include "NetData.h"
#include "IPv4MappedIPv6.h"

NetData IPv4MappedIPv6::extractIPv4NetData(const NetData &ip6NetData) {
    regex ipRegex("0{16}F{4}0{4}([0-9A-Z]{8})");
    smatch match;

    struct NetData netData = {"", "", "", ""};

    if (regex_search(ip6NetData.localIp, match, ipRegex)) {
        netData.localIp = match[1].str().c_str();
        netData.localPort = ip6NetData.localPort;
    }

    if (regex_search(ip6NetData.remoteIp, match, ipRegex)) {
        netData.remoteIp = match[1].str().c_str();
        netData.remotePort = ip6NetData.remotePort;
    }

    return netData;
}
