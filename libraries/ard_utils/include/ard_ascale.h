
#ifndef ARD_ASCALE_H
#define ARD_ASCALE_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ArdAScale {
    int pin;
    struct {
        double a;
        double b;
    } scale;
    struct {
        int min;
        int max;
    } limits_input;
} ArdAScale;

/**
 * @brief      Set linear scale and offset for analog input
 *
 * @param      asc      Analog scaling object
 * @param[in]  in_min   Limit minimum for analog input
 * @param[in]  in_max   Limit maximum for analog input
 * @param[in]  out_min  Minimum output (scaled to output values)
 * @param[in]  out_max  Maximum output (scaled to output values)
 */
inline void ard_asc_set_scale(struct ArdAScale *asc,
                              const int in_min,  const int in_max,
                              const int out_min, const int out_max) {

    asc->limits_input.min = in_min;
    asc->limits_input.max = in_max;

    asc->scale.a = ((double) (out_max - out_min)) / ((double) (asc->limits_input.max - asc->limits_input.min));
    asc->scale.b = (double) out_min;

}

/**
 * @brief      Linearly scale and saturate analog signal
 *
 * @param      asc   Analog scaling object
 *
 * @return     Scaled value from analog input
 */
inline double ard_asc_scale_input(struct ArdAScale *asc) {

    // read analog
    int in = analogRead(asc->pin);
    // saturate input
    if (in < asc->limits_input.min) {
        in = asc->limits_input.min;
    } else if  (in > asc->limits_input.max) {
        in = asc->limits_input.max;
    }
    // scale and offset
    return ((double) (in - asc->limits_input.min)) * asc->scale.a + asc->scale.b;

}

#ifdef __cplusplus
}
#endif

#endif
