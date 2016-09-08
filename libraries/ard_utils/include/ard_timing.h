
#ifndef ARD_TIMING_H
#define ARD_TIMING_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ARD_TIMING_MAX_COUNT
#define ARD_TIMING_MAX_COUNT 10
#endif

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
        // moving target loop until caught up or max iterations reached
        for (int k = 0; k < ARD_TIMING_MAX_COUNT; ++k) {
            timing->prev += timing->ts;
            if (timing->now - timing->prev < timing->ts) {
                break;
            }
        }
        return true;
    }
    return false;
}

typedef struct ArdTimingTimeout {
    bool isset;
    unsigned long prev;
    unsigned long wait_us;
} ArdTimingTimeout;

inline void ard_timing_timeout_set(ArdTimingTimeout *timing, const unsigned long now, const unsigned long wait_us) {
    timing->isset = true;
    timing->prev = now;
    timing->wait_us = wait_us;
}

inline bool ard_timing_timeout_check(ArdTimingTimeout *timing, const unsigned long now) {
    if (timing->isset && now - timing->prev > timing->wait_us) {
        timing->isset = false;
        return true;
    }
    return false;
}

#ifdef __cplusplus
}
#endif

#endif
