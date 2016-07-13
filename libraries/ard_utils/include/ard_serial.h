
#ifndef ARD_SERIAL_H
#define ARD_SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "ard_crc.h"

// wrap arduino C++ code
void ard_serial_begin(const long baud_rate);
void ard_serial_write(const unsigned char in);

typedef struct ArdSerialPacket {
    unsigned char *packet;
    unsigned char *data;
    size_t size;
    char delimiter;
} ArdSerialPacket;

inline void ard_serial_alloc(ArdSerialPacket *serial, const uint16_t size, const unsigned char delimiter) {
    // packet format:
    //  0: delimiter
    //  1 to 2: uint16_t number of bytes (size)
    //  3 to (3+size-1): data
    //  (3+size) to (3+size+1): appended crc
    serial->packet = (unsigned char *) calloc((size_t) size + 5, sizeof(unsigned char));
    // alias
    serial->data = &serial->packet[3];
    // initialize
    serial->delimiter = delimiter;
    serial->size = (size_t) size;

    // write packet header
    serial->packet[0] = delimiter;
    memcpy(&serial->packet[1], &size, sizeof(uint16_t));
}

inline void ard_serial_write_packet(ArdSerialPacket *serial) {
    ard_crc16_ccitt_append(serial->packet, serial->size + 3);
    for (size_t i = 0; i < serial->size + 5; i++) {
        ard_serial_write(serial->packet[i]);
    }
}

inline void ard_serial_free(ArdSerialPacket *serial) {
    free(serial->packet);
    serial->data = NULL;
    serial->size = 0;
}

#ifdef __cplusplus
}
#endif

#endif
