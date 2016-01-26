#include "InodeIpHelper.h"

vector<NetData> InodeIpHelper::filterProccessIp(const vector<string>& socketInodes, const unordered_map<string, NetData>& inodeIps) {
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
