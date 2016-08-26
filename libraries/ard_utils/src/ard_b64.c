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

#include "ard_b64.h"

extern void ro_b64_encodeblock (const uint8_t in[3], uint8_t out[4], const size_t len_in);
extern int ro_b64_decodeblock (const uint8_t in[4], uint8_t out[3], const size_t len_out);

extern int ro_b64_encode (const uint8_t *restrict dec, const size_t len_dec,
                          uint8_t *restrict enc, const size_t len_enc);
extern int ro_b64_decode (const uint8_t *restrict enc, const size_t len_enc,
                          uint8_t *restrict dec, const size_t len_dec);
