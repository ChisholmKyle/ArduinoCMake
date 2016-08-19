
#include "ard_traj.h"

extern int ard_traj_seq_step(ArdTrajSeq *seq);
extern bool ard_traj_seq_timed_step(ArdTrajSeqTimed *seq_timed, int *seq_out, const unsigned long time_us);
extern void ard_traj_seq_timed_reset(ArdTrajSeqTimed *seq_timed, const unsigned long time_us);
