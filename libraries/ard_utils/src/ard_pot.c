
#include "ard_pot.h"

extern void ard_pot_set_scale(struct ArdPot *pot, 
                              const int in_min,  const int in_max, 
                              const int out_min, const int out_max);

extern double ard_pot_scale_input(struct ArdPot *pot, int in);
