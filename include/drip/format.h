#ifndef DRIP_FORMAT_H
#define DRIP_FORMAT_H

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

/** @brief Timestamp epoch (2019-01-01 00:00:00 UTC as Unix timestamp). */
#define DRIP_TIMESTAMP_EPOCH 1546300800

#define DRIP_HI_SIZE 32
#define DRIP_SIGNATURE_SIZE 64

typedef uint8_t drip_hi_t[DRIP_HI_SIZE];
typedef uint8_t drip_signature_t[DRIP_SIGNATURE_SIZE];

static_assert(sizeof(drip_hi_t) == DRIP_HI_SIZE, "drip_hi_t size mismatch");
static_assert(sizeof(drip_signature_t) == DRIP_SIGNATURE_SIZE, "drip_signature_t size mismatch");

typedef enum {
    DRIP_SUCCESS = 0,
    DRIP_ERROR_NULL_POINTER = -1,
    DRIP_ERROR_BUFFER_TOO_SMALL = -2,
    DRIP_ERROR_BUFFER_TOO_LARGE = -3,
    DRIP_ERROR_ARRAY_FULL = -4,
    DRIP_ERROR_INVALID_INDEX = -5,
    DRIP_ERROR_CALLBACK_FAILED = -6,
    DRIP_ERROR_INVALID_LENGTH = -7,
    DRIP_ERROR_INVALID_SAM_TYPE = -8,
    DRIP_ERROR_OUT_OF_RANGE = -9,
    DRIP_ERROR_INVALID_IPV6_PREFIX = -10,
    DRIP_ERROR_VERIFICATION_FAILED = -11,
    DRIP_ERROR_INVALID_TIMESTAMP = -12,
    DRIP_ERROR_INVALID_CHILD_DET = -13,
    DRIP_ERROR_INVALID_PARENT_DET = -14,
    DRIP_ERROR_INVALID_HHSI = -15,
    DRIP_ERROR_INVALID_IPV6_STRING = -16,
} drip_status_t;

typedef enum {
    DRIP_SAM_TYPE_LINK = 0x01,
    DRIP_SAM_TYPE_WRAPPER = 0x02,
    DRIP_SAM_TYPE_MANIFEST = 0x03,
    DRIP_SAM_TYPE_FRAME = 0x04,
} drip_sam_type_t;

#endif
