#include "InodeIpHelper.h"

vector<NetData> InodeIpHelper::filterProccessIp(vector<string> socketInodes, map<string, NetData> inodeIps) {
    vector<NetData> filteredResult;

    for (auto socketInode: socketInodes) {
        for (auto inodeIp: inodeIps) {
            if (socketInode == inodeIp.first) {
                filteredResult.push_back(inodeIp.second);
                break;
            }
        }
    }

    return filteredResult;
}
