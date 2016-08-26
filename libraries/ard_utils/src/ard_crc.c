/**
 * @file       ard_crc.c
 * @author     Kyle Chisholm (dev@kylechisholm.ca)
 * @brief      16-bit Cyclic Redundancy Check (crc16-ccitt)
 *
 * @details
 *
 * Cyclic redundancy check. See group @ref ArdCrc
 *
 */

#include "ard_crc.h"

extern uint16_t ro_crc16_ccitt(const uint8_t *restrict data, const size_t len, const uint16_t seed, const uint16_t final);

extern bool ro_crc16_ccitt_test(const uint8_t *restrict data, const size_t len);
extern uint16_t ro_crc16_ccitt_append(uint8_t *restrict data, const size_t len);
