#ifndef GF_H
#define GF_H

#include <stdint.h>
#include "qruov.h"

static inline uint8_t gf_reduce(uint32_t x)
{
    return x % QRUOV_q;
}

static inline uint8_t gf_add(uint8_t a, uint8_t b)
{
    return gf_reduce(a + b);
}

static inline uint8_t gf_sub(uint8_t a, uint8_t b)
{
    return gf_reduce(a + QRUOV_q - b);
}

static inline uint8_t gf_mul(uint8_t a, uint8_t b)
{
    return gf_reduce((uint32_t)a * b);
}

/*
 * a^(q-2) = a^-1 in GF(q) by Fermat, and 0 maps to 0 as the old table did.
 * The loop branches only on bits of the public constant q - 2, so unlike a
 * table lookup this touches no memory indexed by a.
 */
static inline uint8_t gf_inv(uint8_t a)
{
    uint8_t r = 1;
    uint8_t b = a;
    for (unsigned int e = QRUOV_q - 2; e != 0; e >>= 1) {
        if (e & 1) r = gf_mul(r, b);
        b = gf_mul(b, b);
    }
    return r;
}

#endif // GF_H
