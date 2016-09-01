
#ifndef ARD_HONEYP_H
#define ARD_HONEYP_H

#include <stdint.h>

// bits in hex
#define ARD_HONEYP_BIT_0  0x01
#define ARD_HONEYP_BIT_1  0x02
#define ARD_HONEYP_BIT_2  0x04
#define ARD_HONEYP_BIT_3  0x08
#define ARD_HONEYP_BIT_4  0x10
#define ARD_HONEYP_BIT_5  0x20
#define ARD_HONEYP_BIT_6  0x40
#define ARD_HONEYP_BIT_7  0x80

// address
#define ARD_HONEYP_ADDRESS_DEFAULT 0x28

// scaling
#define ARD_HONEYP_SCALE_90P_14BIT 14745
#define ARD_HONEYP_SCALE_10P_14BIT 1638

typedef struct ArdHoneyp {
    struct {
        double a;
        double b;
    } scale;
    struct {
        uint16_t umin;
        uint16_t umax;
        double pmin;
        double pmax;
    } limits;
    uint8_t preg;
} ArdHoneyp;

int ard_honeyp_read_raw(const uint8_t reg_addr, uint16_t *data);

inline void ard_honeyp_setscale(ArdHoneyp * pr) {
    pr->scale.a = ((double) (pr->limits.pmax - pr->limits.pmin)) / ((double) (ARD_HONEYP_SCALE_90P_14BIT - ARD_HONEYP_SCALE_10P_14BIT));
    pr->scale.b = (double) pr->limits.pmin;
    pr->limits.umin = ARD_HONEYP_SCALE_10P_14BIT;
    pr->limits.umax = ARD_HONEYP_SCALE_90P_14BIT;
}

/**
 * @brief      Read i2c honeywell pressure sensor
 *
 * @param      pr    { parameter_description }
 * @param      out   output (psi)
 *
 * @return     { description_of_the_return_value }
 */
inline int ard_honeyp_read(ArdHoneyp * pr, double *out) {

    /* sensor: pressure */
    uint16_t raw_val;
    int retval = ard_honeyp_read_raw(pr->preg, &raw_val);
    if (retval >= 0) {
        // saturate input
        if (raw_val < pr->limits.umin) {
            raw_val = pr->limits.umin;
            retval = 2;
        } else if  (raw_val > pr->limits.umax) {
            raw_val = pr->limits.umax;
            retval = 2;
        }
        // scale and offset
        (*out) = ((double) (raw_val - pr->limits.umin)) * pr->scale.a + pr->scale.b;
    }
    return retval;

}


#endif
