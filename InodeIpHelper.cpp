#include "InodeIpHelper.h"

vector<NetData> InodeIpHelper::filterProccessIp(vector<string> socketInodes, unordered_map<string, NetData> inodeIps) {
    vector<NetData> filteredResult;
    filteredResult.reserve(100);

    for (auto socketInode: socketInodes) {
        auto inodeIp = inodeIps.find(socketInode);
        if (inodeIp != inodeIps.end()) {
            filteredResult.push_back(inodeIp->second);
        }
    }

    return filteredResult;
}
