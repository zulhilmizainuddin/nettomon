#include "ProcNetPublisher.h"

void ProcNetPublisher::setNetData(const vector<NetData> &tcpNetData, const vector<NetData> &udpNetData, const vector<NetData> &tcp6NetData,
                                  const vector<NetData> &udp6NetData) {
    this->tcpNetData = tcpNetData;
    this->udpNetData = udpNetData;
    this->tcp6NetData = tcp6NetData;
    this->udp6NetData = udp6NetData;
}

void ProcNetPublisher::registerObserver(ProcNetObserver * observer) {
    observers.push_back(observer);
}

void ProcNetPublisher::notifyObservers() {
    for (ProcNetObserver * observer: observers) {
        observer->updateNetData(tcpNetData, udpNetData, tcp6NetData, udp6NetData);
    }
}
