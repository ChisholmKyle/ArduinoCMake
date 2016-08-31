
#ifndef ARD_HONEYP_H
#define ARD_HONEYP_H

#include "Arduino.h"
#include "Wire.h"

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
#define ARD_HONEYP_ADDRESS 0x28

// read bit
#define ARD_HONEYP_READ_BIT ARD_HONEYP_BIT_0

#ifdef __cplusplus
extern "C" {
#endif

inline int ard_honeyp_read_raw(uint16_t *data) {

    uint8_t bytes_in[2] = {0};

    Wire.requestFrom(ARD_HONEYP_ADDRESS, 2, 1);
    if (Wire.available() >= 2)  {
        bytes_in[0] = Wire.read();
        bytes_in[1] = Wire.read();
    } else {
        return -1;
    }

    /* diagnostics */
    uint8_t s = bytes_in[0] >> 6;

    /* bit-shift to 14-bits and copy data */
    bytes_in[0] &= 0x3f;
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

#ifdef __cplusplus
}
#endif

#endif
