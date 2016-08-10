/**
 * @file       ard_crc.h
 * @author     Kyle Chisholm (dev@kylechisholm.ca)
 * @brief      16-bit Cyclic Redundancy Check (crc16-ccitt)
 *
 * @details
 *
 * Cyclic redundancy check. See group @ref ArdCrc
 *
 */

#ifndef ARD_CRC_H
#define ARD_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @defgroup   ArdCrc Cyclic Redundancy Check
 * @brief      Cyclic redundancy check, typically for serial communications
 *
 * @{
 *
 */

/**
 * @brief      Tests a byte array (unsigned char) appended with a crc checksum
 *             to see if the message is intact.
 *
 * @param[in]  data  Byte (unsigned char) array with appended CRC checksum
 * @param[in]  len   Length of input array (number of bytes) including
 *                   the 2 checksum bytes appended to the array
 *
 * @return     Boolean `true` if checksum for the array is valid, `false` otherwise
 */
bool ard_crc16_ccitt_test(const uint8_t *data, const size_t len);



/**
 * @brief      Appends CRC checksum to data array.
 *
 * @param      data  The data array to append the CRC checksum. This array
 *                   must be contiguous in memory with 2 extra bytes so that the
 *                   CRC checksum can be appended.
 * @param[in]  len   The length of the data array (number of bytes) not including
 *                   the two extra bytes required for the appended array.
 *
 * @return     The CRC checksum. The data input parameter is also appended with
 *             the 2 checksum bytes.
 */
uint16_t ard_crc16_ccitt_append(uint8_t *data, const size_t len);


/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
