#ifndef DRIP_FORMAT_H
#define DRIP_FORMAT_H

#include <stddef.h>
#include <stdint.h>

typedef enum {
    DRIP_SUCCESS = 0,
    DRIP_ERROR_NULL_POINTER = -1,
    DRIP_ERROR_ARRAY_FULL = -2,
    DRIP_ERROR_INVALID_INDEX = -3,
    DRIP_ERROR_SIGNING_FAILED = -4,
    DRIP_ERROR_VERIFICATION_FAILED = -5,
    DRIP_ERROR_HASHING_FAILED = -6,
} drip_status_t;

#endif
