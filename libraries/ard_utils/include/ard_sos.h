
#ifndef ARD_SOS_H
#define ARD_SOS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum ArdFilterType {
    EARD_SOS_LOW,
    EARD_SOS_HIGH,
    EARD_SOS_BAND,
    EARD_SOS_STOP
} ArdFilterType;

/*
    Second-order (biquadratic) IIR digital filtering
    freq:   control loop frequency
    w:      relative cutoff frequency
    sos:    matrix, size (num_scns x 6)
            where num_scns is sos matrix rows (number of sections)
            For butterworth pass filter, num_scns = ceil(order/2).
    z: state of 4 previous inputs for each sos, size (4 x num_scns)
 */
typedef struct ArdSosFilter {
    double **(z[4]);
    double freq;
    double w[2];
    double *sos;
    ArdFilterType type;
    size_t num_scns;
} ArdSosFilter;

/* run filter */
void ard_sos_run (ArdSosFilter *filt, double restrict* x);

#ifdef __cplusplus
}
#endif

#endif
