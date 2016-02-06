#include "Duration.h"

chrono::steady_clock::time_point Duration::start() {
    return startTime = chrono::steady_clock::now();
}

chrono::steady_clock::time_point Duration::end() {
    return endTime = chrono::steady_clock::now();
}

long Duration::inMilliSeconds() {
    return chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
}

long Duration::inMicroSeconds() {
    return chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
}

long Duration::inNanoSeconds() {
    return chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count();
}
