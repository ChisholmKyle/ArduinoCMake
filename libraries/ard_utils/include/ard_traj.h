
#ifndef ARD_TRAJ_H
#define ARD_TRAJ_H

#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ArdTrajSeq {
    int **out;
    size_t mode;
    size_t index;
    struct {
        size_t steps;
        size_t modes;
    } num;
} ArdTrajSeq;

typedef struct ArdTrajSeqTimed {
    ArdTrajSeq seq;
    int *timing_ms;
    int target_ms;
} ArdTrajSeqTimed;

/**
 * @brief      Step through sequence
 *
 * @param      seq   Sequence container
 *
 * @return     { description_of_the_return_value }
 */
inline int ard_traj_seq_step(ArdTrajSeq *seq) {
    int out = seq->out[seq->mode][seq->index++];
    if (seq->index == seq->num.steps) seq->index = 0;
    return out;
}

/**
 * @brief      { function_description }
 *
 * @param      seq_timed  The sequence timed
 * @param      seq_out    The sequence out
 * @param[in]  time_ms    The time milliseconds
 *
 * @return     { description_of_the_return_value }
 */
inline bool ard_traj_seq_timed_step(ArdTrajSeqTimed *seq_timed, int *seq_out, const int time_ms) {
    if (time_ms - seq_timed->target_ms > seq_timed->timing_ms[seq_timed->seq.index]) {
     // ||
     //    (dt_scale * ((double) (time_ms - seq_timed->target_ms)) > (double) seq_timed->timing_ms[seq_timed->seq.index])) {
        /* advance step  */
        seq_timed->seq.index += 1;
        if (seq_timed->seq.index == seq_timed->seq.num.steps) seq_timed->seq.index = 0;
        seq_timed->target_ms += seq_timed->timing_ms[seq_timed->seq.index];
        *seq_out = seq_timed->seq.out[seq_timed->seq.mode][seq_timed->seq.index];
        return true;
    } else {
        *seq_out = seq_timed->seq.out[seq_timed->seq.mode][seq_timed->seq.index];
        return false;
    }
}

#ifdef __cplusplus
}
#endif

#endif
