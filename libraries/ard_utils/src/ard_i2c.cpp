
#include <Arduino.h>
#include <Wire.h>

#include <stdbool.h>
#include <stdint.h>

#include "ard_i2c.h"

// slave
void ard_i2c_slave_setup(const uint8_t slave_address, ArdI2CReqHandler request_handler, ArdI2CRecHandler receive_handler) {
    Wire.onRequest(request_handler);
    Wire.onReceive(receive_handler);
    Wire.begin(slave_address);
}

// master write to slave
size_t ard_i2c_slave_write(uint8_t *data, const size_t size) {
    if (size <= BUFFER_LENGTH) {
        return Wire.write(data, (uint8_t) size);
    } else {
        // need multiple calls to send all the data
        size_t remaining = size;
        size_t retval;
        while (remaining > BUFFER_LENGTH) {
            retval = Wire.write(&data[size - remaining], BUFFER_LENGTH);
            if (retval != BUFFER_LENGTH) {
                return size - remaining + retval;
            };
            remaining = remaining - BUFFER_LENGTH;
        }
        // last call
        retval = Wire.write(&data[size - remaining], (uint8_t) remaining);
        if (retval != remaining) {
            return size - remaining + retval;
        } else {
            return size;
        }
    }
}

void ard_i2c_master_begin() {
    Wire.begin();
}


uint8_t ard_i2c_master_write_register(const uint8_t device_address, const uint8_t write_register, const uint8_t register_value) {
    // Writes value at i2c register
    Wire.beginTransmission(device_address);
    Wire.write(write_register);
    Wire.write(register_value);
    return Wire.endTransmission(true);
}

uint8_t ard_i2c_master_read_begin(const uint8_t device_address, const uint8_t start_register) {
    // read bytes (size bytes) into out
    Wire.beginTransmission(device_address);
    Wire.write(start_register);
    return Wire.endTransmission(false);
}

size_t ard_i2c_master_read(const uint8_t device_address, uint8_t *out, const size_t size) {
    // read bytes (size bytes) into out
    if (size <= BUFFER_LENGTH) {
        // only one requestFrom call to get all the data
        Wire.requestFrom(device_address, (uint8_t) size, (uint8_t) true);
        if (((size_t) Wire.available()) < size) return 0;
        for (size_t i = 0; i < size; i++) {
            out[i] = Wire.read();
        }
    } else {
        // need multiple requestFrom calls to get all the data
        size_t remaining = size;
        while (remaining > BUFFER_LENGTH) {
            Wire.requestFrom(device_address, (uint8_t) BUFFER_LENGTH, (uint8_t) false);
            if (((size_t) Wire.available()) < BUFFER_LENGTH) return size - remaining;
            for (size_t i = 0; i < BUFFER_LENGTH; i++) {
                out[size - remaining + i] = Wire.read();
            }
            remaining = remaining - BUFFER_LENGTH;
        }
        // last call
        Wire.requestFrom(device_address, (uint8_t) remaining, (uint8_t) true);
        if (((size_t) Wire.available()) < remaining) return size - remaining;
        for (size_t i = 0; i < remaining; i++) {
            out[size - remaining + i] = Wire.read();
        }
    }
    return size;
}

size_t ard_i2c_master_read_16swap(const uint8_t device_address, uint16_t *out, const size_t num_values) {
    // CAREFUL: num_values must be less than or equal to BUFFER_LENGTH / 2
    Wire.requestFrom(device_address, (uint8_t) 2 * num_values, (uint8_t) true);
    if (((size_t) Wire.available() / 2) < num_values) return 0;
    uint8_t work[2];
    size_t i;
    for (i = 0; i < num_values; i++) {
        work[1] = Wire.read();
        work[0] = Wire.read();
        memcpy(&out[i], work, sizeof(uint16_t));
    }
    return num_values;
}

uint8_t ard_i2c_master_end_transmission(void) {
    return Wire.endTransmission(true);
}
