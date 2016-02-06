#ifndef NETTOMON_DURATION_H
#define NETTOMON_DURATION_H

#include <chrono>

using namespace std;

class Duration {
private:
    chrono::steady_clock::time_point startTime;
    chrono::steady_clock::time_point endTime;

public:
    chrono::steady_clock::time_point start();
    chrono::steady_clock::time_point end();
    long  inMilliSeconds();
    long  inMicroSeconds();
    long  inNanoSeconds();
};


#endif //NETTOMON_DURATION_H
