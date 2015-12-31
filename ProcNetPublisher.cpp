#include "ProcNetPublisher.h"

void ProcNetPublisher::setNetData(vector<NetData> tcpNetData, vector<NetData> udpNetData) {
    this->tcpNetData = tcpNetData;
    this->udpNetData = udpNetData;
}

void ProcNetPublisher::registerObserver(ProcNetObserver * observer) {
    observers.push_back(observer);
}

void ProcNetPublisher::notifyObservers() {
    for (ProcNetObserver * observer: observers) {
        observer->updateNetData(tcpNetData, udpNetData);
    }
}
