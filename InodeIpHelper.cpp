#include "InodeIpHelper.h"

vector<NetData> InodeIpHelper::filterProccessIp(const vector<string>& socketInodes, const unordered_map<string, NetData>& inodeIps) {
    vector<NetData> filteredResult;
    filteredResult.reserve(100);

    #pragma omp parallel for
    for (int i = 0; i < socketInodes.size(); ++i) {
        auto inodeIp = inodeIps.find(socketInodes[i]);
        if (inodeIp != inodeIps.end()) {
            #pragma omp critical(inodeip)
            filteredResult.push_back(inodeIp->second);
        }
    }

    return filteredResult;
}
