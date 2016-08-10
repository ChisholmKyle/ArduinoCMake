
#include "ard_ascale.h"

extern void ard_asc_set_scale(struct ArdAScale *asc,
                              const int in_min,  const int in_max,
                              const int out_min, const int out_max);
extern double ard_asc_scale_input(struct ArdAScale *asc);
