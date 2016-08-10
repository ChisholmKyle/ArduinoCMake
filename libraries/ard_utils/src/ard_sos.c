
#include "ard_sos.h"

static inline void ro_filter_direct_form_II_transposed (double * x,
                                                        double * z,
                                                        const double * b,
                                                        const double * a)
{
    /* shift z */
    z[1] = z[0];
    z[3] = z[2];
    /* output */
    double y = (*x) * b[0] + z[1];
    /* calculate new z values */
    z[2] = (*x) * b[2] - y * a[2];
    z[0] = (*x) * b[1] - y * a[1] + z[3];
    /* update x */
    (*x) = y;
}

void ro_sos_run (ArdSosFilter *filt, double * x)
{
    for (size_t j = 0; j < filt->num_scns; j++) {
        ro_filter_direct_form_II_transposed (x, /* x */
                                             &(filt->z[j * 4]) /* z_i */,
                                             &(filt->sos[j * 6 + 0]), /* b */
                                             &(filt->sos[j * 6 + 3]) /* a */);
    }
}
