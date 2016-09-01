
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
    unsigned long target_us;
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
inline bool ard_traj_seq_timed_step(ArdTrajSeqTimed *seq_timed, int *seq_out, const unsigned long time_us) {
    /* target delta  */
    unsigned long target_delta_us = 1000 * ((unsigned long) seq_timed->timing_ms[seq_timed->seq.index]);
    if ( (time_us - seq_timed->target_us) > target_delta_us) {
        /* output  */
        *seq_out = seq_timed->seq.out[seq_timed->seq.mode][seq_timed->seq.index];
        /* new target time */
        seq_timed->target_us += target_delta_us;
        /* advance step  */
        seq_timed->seq.index += 1;
        if (seq_timed->seq.index == seq_timed->seq.num.steps) seq_timed->seq.index = 0;
        return true;
    } else {
        // *seq_out = seq_timed->seq.out[seq_timed->seq.mode][seq_timed->seq.index];
        return false;
    }
}

/**
 * @brief      { function_description }
 *
 * @param      seq_timed  The sequence timed
 * @param[in]  time_us    The time us
 * @param[in]  delay_us   The delay us
 */
inline void ard_traj_seq_timed_reset(ArdTrajSeqTimed *seq_timed, const unsigned long time_us) {
    seq_timed->target_us = time_us;
    seq_timed->seq.index = 0;
}

#ifdef __cplusplus
}
#endif

#endif
