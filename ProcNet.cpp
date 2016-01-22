#include <fstream>
#include <algorithm>
#include <regex>
#include "ProcNet.h"

unordered_map<string, NetData> ProcNet::getInodesIpMap() {
    auto inodeIpMapList = retrieveInodeIpMapping();

    return inodeIpMapList;
}

unordered_map<string, NetData> ProcNet::retrieveInodeIpMapping() {
    string filename = "/proc/net/" + ipType;

    ifstream file(filename);
    string store;
    unordered_map<string, NetData> inodesIpMap;
    inodesIpMap.reserve(100);

    while (getline(file, store)) {
        string header("sl  local_address rem_address   st tx_queue rx_queue tr tm->when retrnsmt   uid  timeout inode");
        if (store.find(header) == string::npos) {
            auto first = store.find_first_not_of(" ");
            auto last = store.find_last_not_of(" ");

            string ipTypeData = store.substr(first, last - first + 1);

            inodesIpMap.insert(extractInodeIpMapping(ipTypeData));
        }
    }

    return inodesIpMap;
}

pair<string, NetData> ProcNet::extractInodeIpMapping(string ipTypeData) {
    regex ipTypeDataRegex("^\\d+:\\s+([0-9A-Z]+):([0-9A-Z]+)\\s+([0-9A-Z]+):([0-9A-Z]+)(?:\\s+.+?){6}\\s+([0-9]+)");
    smatch match;

    struct NetData netData;
    if (regex_search(ipTypeData, match, ipTypeDataRegex)) {

        netData = {
            match[1].str().c_str(),
            match[2].str().c_str(),
            match[3].str().c_str(),
            match[4].str().c_str()
        };
    }

    return pair<string, NetData>(match[5].str().c_str(), netData);
}
