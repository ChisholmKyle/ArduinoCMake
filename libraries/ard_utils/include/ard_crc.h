
#ifndef ARD_CRC_H
#define ARD_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

bool ard_crc16_ccitt_test(const unsigned char *data, const size_t len);
uint16_t ard_crc16_ccitt_append(unsigned char *data, const size_t len);

#ifdef __cplusplus
}
#endif

#endif
