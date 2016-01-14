#ifndef NETTOMON_PROCREADTIMERDATA_H
#define NETTOMON_PROCREADTIMERDATA_H

#include <string>
#include "ProcNetPublisher.h"

struct ProcReadTimerData {
    string pid;
    int interval;
};

#endif //NETTOMON_PROCREADTIMERDATA_H
