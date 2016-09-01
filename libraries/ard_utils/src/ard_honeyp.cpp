
#include "Arduino.h"
#include "Wire.h"
#include "ard_honeyp.h"

int ard_honeyp_read_raw(const uint8_t reg_addr, uint16_t *data) {

    uint8_t bytes_in[2] = {0};

    Wire.requestFrom(reg_addr, (uint8_t) 2, (uint8_t) 1);
    if (Wire.available() >= 2)  {
        bytes_in[1] = Wire.read();
        bytes_in[0] = Wire.read();
    } else {
        return -1;
    }

    /* diagnostics */
    uint8_t s = bytes_in[1] >> 6;

    /* bit-shift to 14-bits and copy data */
    bytes_in[1] &= 0x3f;
    memcpy(data, bytes_in, sizeof(uint16_t));

    if (s == 0) {
        /* new data */
        return 0;
    } else if (s == 2) {
        /* stale data */
        return 1;
    } else {
        /* error */
        return -1;
    }
}

extern void ard_honeyp_setscale(ArdHoneyp * pr, const double pmin, const double pmax);
extern int ard_honeyp_read(ArdHoneyp * pr, double *out);
