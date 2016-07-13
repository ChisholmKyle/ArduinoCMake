
#ifndef ARD_I2C_H
#define ARD_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

// i2c communications handlers for slave
typedef void (*ArdI2CReqHandler)(void);
typedef void (*ArdI2CRecHandler)(int);

// slave
void ard_i2c_slave_setup(const uint8_t slave_address, ArdI2CReqHandler request_handler, ArdI2CRecHandler receive_handler);
size_t ard_i2c_slave_write(uint8_t *data, const size_t size);

// master
void    ard_i2c_master_begin();
uint8_t ard_i2c_master_write_register(const uint8_t device_address, const uint8_t write_register, const uint8_t register_value);
uint8_t ard_i2c_master_read_begin(const uint8_t device_address, const uint8_t start_register);
size_t  ard_i2c_master_read(const uint8_t device_address, uint8_t *out, const size_t size);
size_t  ard_i2c_master_read_16swap(const uint8_t device_address, uint16_t *out, const size_t num_values);
uint8_t ard_i2c_master_end_transmission(void);

#ifdef __cplusplus
}
#endif

#endif
