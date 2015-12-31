#ifndef NETTOMON_PROCREADTIMERDATA_H
#define NETTOMON_PROCREADTIMERDATA_H

#include <string>
#include "ProcNetPublisher.h"

struct ProcReadTimerData {
    string pid;
    ProcNetPublisher* publisher;
};

#endif //NETTOMON_PROCREADTIMERDATA_H
