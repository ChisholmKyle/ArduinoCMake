
#ifndef ARD_SPLINE_H
#define ARD_SPLINE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>

/* spline evaluation */
inline double ard_spline_eval(const double x,
                                  const double *coefs,
                                  const double x_per_break,
                                  const unsigned int num_breaks) {

    unsigned int i = floor(x * ((double) num_breaks));
    if (i == num_breaks) i = 0;

    const double xs = x - x_per_break * ((double) i);

    return (coefs[i] * xs * xs * xs + coefs[i + 1 * num_breaks] * xs * xs + coefs[i + 2 * num_breaks] * xs + coefs[i + 3 * num_breaks]);

}

#ifdef __cplusplus
}
#endif

#endif
