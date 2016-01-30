#ifndef NETTOMON_PROCREADTIMER_H
#define NETTOMON_PROCREADTIMER_H


class ProcReadTimer : public ProcNetPublisher {
public:
    ProcReadTimer();

    void start(const char *pid);
};


#endif //NETTOMON_PROCREADTIMER_H