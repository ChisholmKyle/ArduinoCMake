/**
 * @file       ard_i2c.h
 * @author     Kyle Chisholm (dev@kylechisholm.ca)
 * @brief      C wrapper for I2C Communications with the Arduino
 *
 * @details
 *
 * C wrapper for I2C Communications. See group @ref ArdI2C
 *
 */

#ifndef ARD_I2C_H
#define ARD_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

/**
 * @defgroup   ArdI2C I2C Communications.
 * @brief      C wrapper for I2C Communications.
 *
 * @{
 *
 */

/** @brief function pointer for handling i2C requests from a master device */
typedef void (*ArdI2CReqHandler)(void);

/** @brief function pointer for receiving data from an i2C master device */
typedef void (*ArdI2CRecHandler)(int);

/**
 * @brief      Setup as a slave device for I2C communications
 *
 * @param[in]  slave_address    The slave device address
 * @param[in]  request_handler  The request handler
 * @param[in]  receive_handler  The receive handler
 */
void ard_i2c_slave_setup(const uint8_t slave_address, ArdI2CReqHandler request_handler, ArdI2CRecHandler receive_handler);


/**
 * @brief      Write data as a slave to master device
 *
 * @param      data  Array of data (bytes)
 * @param[in]  size  Size of data array (number of bytes)
 *
 * @return     Length of data sent to master
 */
size_t ard_i2c_slave_write(uint8_t *data, const size_t size);


void    ard_i2c_master_begin();
uint8_t ard_i2c_master_write_register(const uint8_t device_address, const uint8_t write_register, const uint8_t register_value);
uint8_t ard_i2c_master_read_begin(const uint8_t device_address, const uint8_t start_register);
size_t  ard_i2c_master_read(const uint8_t device_address, uint8_t *out, const size_t size);
size_t  ard_i2c_master_read_16swap(const uint8_t device_address, uint16_t *out, const size_t num_values);
uint8_t ard_i2c_master_end_transmission(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
