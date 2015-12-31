#ifndef NETTOMON_PROCREADTIMER_H
#define NETTOMON_PROCREADTIMER_H

#include <string>
#include <boost/asio.hpp>
#include "ProcNetPublisher.h"
#include "ProcReadTimerData.h"

using namespace std;
using namespace boost;

class ProcReadTimer {
public:
    void *start(ProcReadTimerData data);
};


#endif //NETTOMON_PROCREADTIMER_H
