
#include <Arduino.h>
#include <stdint.h>

#include "ard_serial.h"

// arduino wrappers
void ard_serial_begin(const long baud_rate) {
    Serial.begin(baud_rate);
}
void ard_serial_write(const unsigned char in) {
    Serial.write(in);
}

extern "C" {

    extern void ard_serial_alloc(ArdSerialPacket *serial, const uint16_t size, const unsigned char delimiter);
    extern void ard_serial_write_packet(ArdSerialPacket *serial);
    extern void ard_serial_free(ArdSerialPacket *serial);

}
