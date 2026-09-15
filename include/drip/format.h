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

/**
 * @brief Specific Session ID (SSI) Type values per RFC 9374.
 *
 * First byte of the 20-byte Remote ID UAS ID when ID type is 4 (SSI).
 *
 * @see https://www.rfc-editor.org/rfc/rfc9374.html#section-4
 * @see https://www.librid.org/latest/api/basic_id/#enum-rid_basic_id_type_t
 */
typedef enum {
    DRIP_SSI_TYPE_DRIP_ENTITY_ID = 0x01,
    DRIP_SSI_TYPE_IEEE_1609_2_HASHED_ID8 = 0x02,
} drip_ssi_type_t;

#endif
