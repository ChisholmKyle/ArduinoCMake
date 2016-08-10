
#include "ard_traj.h"

extern int ard_traj_seq_step(ArdTrajSeq *seq);
extern bool ard_traj_seq_timed_step(ArdTrajSeqTimed *seq_timed, int *seq_out, const int time_ms, const double dt_scale);
