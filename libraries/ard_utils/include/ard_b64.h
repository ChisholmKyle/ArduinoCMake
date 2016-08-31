/**
 * @file       ard_b64.h
 * @author     Kyle Chisholm (dev@kylechisholm.ca)
 * @brief      Base64 encoding and decoding
 *
 * @details
 *
 * See group @ref ArdB64
 *
 */

/**
 * @defgroup   ArdB64 Base64 encoding
 * @brief      Base64 encoding and decoding, typically for serial and networking communications
 *
 * @{
 *
 */

#ifndef ARD_B64_H
#define ARD_B64_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @brief Buffer size macros
 */
#define ARD_B64_BUFFER_ENC_LEN(LENDEC) (((LENDEC + 2) / 3) * 4)
#define ARD_B64_BUFFER_DEC_LEN(LENENC) ((LENENC / 4) * 3)

/* encode 3 8-bit binary bytes as 4 '6-bit' characters */
inline void ard_b64_encodeblock (const uint8_t in[3], uint8_t out[4], const size_t len_in)
{
    /* Translation Table as described in RFC1113 */
    static const char ro_cb64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    out[0] = ro_cb64[ in[0] >> 2 ];
    out[1] = ro_cb64[ ((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4) ];
    out[2] = (len_in > 1 ? ro_cb64[ ((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6) ] : '=');
    out[3] = (len_in > 2 ? ro_cb64[ in[2] & 0x3f ] : '=');
}

inline int ard_b64_decodeblock (const uint8_t in[4], uint8_t out[3], const size_t len_out)
{
    /* decode 4 '6-bit' characters into 3 8-bit binary bytes */
    static const char ro_cd64[] = "|$$$}rstuvwxyz{$$$$$$$>?@ABCDEFGHIJKLMNOPQRSTUVW$$$$$$XYZ[\\]^_`abcdefghijklmnopq";
    uint8_t i, v[4] = {0};
    for (i = 0; i < 4; i++) {
        if ('=' == in[i]) {
            break;
        }
        if (in[i] < 43 || in[i] > 122) {
            return -1;
        }
        v[i] = (uint8_t) ro_cd64[in[i] - 43];
        if (v[i] != '$') {
            v[i] -= 62;
        } else {
            break;
        }
    }
    out[0] = v[0] << 2 | v[1] >> 4;
    if (len_out > 1) {
        out[1] = v[1] << 4 | v[2] >> 2;
        if (len_out > 2) {
            out[2] = (uint8_t) (((v[2] << 6) & 0xc0) | v[3]);
        }
    }
    return 0;
}

inline int ard_b64_encode (const uint8_t *dec, const size_t len_dec,
                          uint8_t *enc, const size_t len_enc)
{
    size_t i = 0, o = 0;
    if (len_enc >= ARD_B64_BUFFER_ENC_LEN(len_dec)) {
        for (i = o = 0; i < len_dec; i += 3, o += 4) {
            ard_b64_encodeblock (dec + i, enc + o, len_dec - i);
        }
    } else {
        return -1;
    }
    return 0;
}

inline int ard_b64_decode (const uint8_t *enc, const size_t len_enc,
                          uint8_t *dec, const size_t len_dec)
{
    size_t i, o;
    if (len_dec <= ARD_B64_BUFFER_DEC_LEN(len_enc)) {
        for (i = o = 0; i < len_enc; i += 4, o += 3) {
            if (ard_b64_decodeblock (enc + i, dec + o, len_dec - o) == -1) {
                return -1;
            }
        }
    } else {
        return -1;
    }
    return 0;
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
