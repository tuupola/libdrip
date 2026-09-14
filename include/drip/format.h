#ifndef DRIP_FORMAT_H
#define DRIP_FORMAT_H

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "drip/error.h"

/** @brief Timestamp epoch (2019-01-01 00:00:00 UTC as Unix timestamp). */
#define DRIP_TIMESTAMP_EPOCH 1546300800

#define DRIP_HI_SIZE 32
#define DRIP_SIGNATURE_SIZE 64

typedef uint8_t drip_hi_t[DRIP_HI_SIZE];
typedef uint8_t drip_signature_t[DRIP_SIGNATURE_SIZE];

static_assert(sizeof(drip_hi_t) == DRIP_HI_SIZE, "drip_hi_t size mismatch");
static_assert(
    sizeof(drip_signature_t) == DRIP_SIGNATURE_SIZE, "drip_signature_t size mismatch"
);

typedef enum {
    DRIP_SAM_TYPE_LINK = 0x01,
    DRIP_SAM_TYPE_WRAPPER = 0x02,
    DRIP_SAM_TYPE_MANIFEST = 0x03,
    DRIP_SAM_TYPE_FRAME = 0x04,
} drip_sam_type_t;

#endif
