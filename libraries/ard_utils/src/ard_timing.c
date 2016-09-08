
#include <stdbool.h>

#include "ard_timing.h"

extern void ard_timing_reset(ArdTiming *timing, const double time_step);
extern bool ard_timing_step(ArdTiming *timing);
extern void ard_timing_timeout_set(ArdTimingTimeout *timing, const unsigned long now, const unsigned long wait_us);
extern bool ard_timing_timeout_check(ArdTimingTimeout *timing, const unsigned long now);
