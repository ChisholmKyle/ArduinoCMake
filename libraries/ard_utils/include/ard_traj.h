
#ifndef ARD_TRAJ_H
#define ARD_TRAJ_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ArdTrajSeq {
    int *out;
    int *timing;
    int seq_steps;
} ArdTrajSeq;

inline void ard_set_scale(struct ArdPot *pot, 
                          const int in_min,  const int in_max, 
                          const int out_min, const int out_max) {

}

#ifdef __cplusplus
}
#endif

#endif
