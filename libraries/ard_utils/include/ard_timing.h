
#ifndef ARD_TIMING_H
#define ARD_TIMING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <Arduino.h>

typedef struct ArdTiming {
    unsigned long prev;
    unsigned long now;
    unsigned long ts;
    double time_step;
} ArdTiming;

inline void ard_timing_reset(ArdTiming *timing, const double time_step) {
    timing->prev = micros();
    timing->now = timing->prev;
    timing->ts = (unsigned long) (time_step * 1.e6);
    timing->time_step = time_step;
}

inline bool ard_timing_step(ArdTiming *timing) {
    timing->now = micros();
    if (timing->now - timing->prev > timing->ts) {
        // moving target
        timing->prev += timing->ts;
        return true;
    }
    return false;
}

#ifdef __cplusplus
}
#endif

#endif
