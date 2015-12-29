#include <fstream>
#include <algorithm>
#include <regex>
#include "ProcNet.h"

map<string, NetData> ProcNet::getInodesIpMap() {
    auto ipTypeData = getIpTypeData();
    auto inodeIpMapList = extractInodesIpMapping(ipTypeData);

    return inodeIpMapList;
}

vector<string> ProcNet::getIpTypeData() {
    string filename = "/proc/net/" + ipType;

    ifstream file(filename);
    string store;
    vector<string> ipTypeDataList;

    while (getline(file, store)) {
        string header("sl  local_address rem_address   st tx_queue rx_queue tr tm->when retrnsmt   uid  timeout inode");
        if (store.find(header) == string::npos) {
            auto first = store.find_first_not_of(" ");
            auto last = store.find_last_not_of(" ");

            ipTypeDataList.push_back(store.substr(first, last - first + 1));
        }
    }

    return ipTypeDataList;
}

map<string, NetData> ProcNet::extractInodesIpMapping(vector<string> ipTypeDataList) {
    map<string, NetData> inodesIpMap;

    for_each(ipTypeDataList.begin(), ipTypeDataList.end(), [&](string ipTypeData) {
        regex ipTypeDataRegex("^\\d+:\\s+([0-9A-Z]+):([0-9A-Z]+)\\s+([0-9A-Z]+):([0-9A-Z]+)(?:\\s+.+?){6}\\s+([0-9]+)");
        smatch match;

        if  (regex_search(ipTypeData, match, ipTypeDataRegex)) {

            NetData netData = {
                    match[1].str().c_str(),
                    match[2].str().c_str(),
                    match[3].str().c_str(),
                    match[4].str().c_str()
            };

            inodesIpMap[match[5].str().c_str()] = netData;
        }
    });

    return inodesIpMap;
}
