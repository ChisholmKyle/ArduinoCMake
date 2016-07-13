
#include <stdbool.h>

#include "ard_timing.h"

extern void ard_timing_reset(ArdTiming *timing, const double time_step);
extern bool ard_timing_step(ArdTiming *timing);
