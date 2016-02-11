#ifndef NETTOMON_PROCREADTIMER_H
#define NETTOMON_PROCREADTIMER_H


#include <string>

class ProcReadTimer : public ProcNetPublisher {
public:
    ProcReadTimer();

    void start(string pid);
};


#endif //NETTOMON_PROCREADTIMER_H