#include "ProcNetPublisher.h"

void ProcNetPublisher::setNetData(const vector<NetData> &ipNetData, const vector<NetData> &ip6NetData) {
    this->ipNetData = ipNetData;
    this->ip6NetData = ip6NetData;
}

void ProcNetPublisher::registerObserver(ProcNetObserver * observer) {
    observers.push_back(observer);
}

void ProcNetPublisher::notifyObservers() {
    for (ProcNetObserver * observer: observers) {
        observer->updateNetData(ipNetData, ip6NetData);
    }
}
