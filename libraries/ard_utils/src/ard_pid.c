
#include <stdbool.h>

#include "ard_pid.h"

extern void ard_pid_reset(ArdPidState *state);

// forwards euler
extern double ard_pid_run_fwd(const double des, const double meas,
                             ArdPidState *state, const double ts,
                             const ArdPidParam *param);
// backwards euler
extern double ard_pid_run_back(const double des, const double meas,
                            ArdPidState *state, const double ts,
                            const ArdPidParam *param);
// trapezoidal
extern double ard_pid_run_trap(const double des, const double meas,
                            ArdPidState *state, const double ts,
                            const ArdPidParam *param);
