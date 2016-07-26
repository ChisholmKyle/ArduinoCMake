
#ifndef ARD_POT_H
#define ARD_POT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ArdPot { 
    int pin;
    struct {
        double a;
        double b;
    } scale;
    struct {
        int min;
        int max;
    } limits_input;
} ArdPot;

inline void ard_pot_set_scale(struct ArdPot *pot, 
                              const int in_min,  const int in_max, 
                              const int out_min, const int out_max) {

    pot->limits_input.max = in_max;
    pot->limits_input.max = in_max;

    pot->scale.a = ((double) (out_max - out_min)) / ((double) (in_max - in_min));
    pot->scale.b = (double) out_min;

}

inline double ard_pot_scale_input(struct ArdPot *pot, int in) {

    // saturate input
    if (in < pot->limits_input.min) {
        in = pot->limits_input.min;
    } else if  (in > pot->limits_input.max) {
        in = pot->limits_input.max;
    }
    // scale and offset
    return ((double) (in - pot->limits_input.min)) * pot->scale.a + pot->scale.b;

}

#ifdef __cplusplus
}
#endif

#endif
