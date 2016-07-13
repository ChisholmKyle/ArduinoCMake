

#include "ard_spline.h"

/* spline evaluation */
extern double ard_traj_spline_eval(const double x,
                                  const double *coefs,
                                  const double x_per_break,
                                  const unsigned int num_breaks);
