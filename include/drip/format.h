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

/**
 * @brief HHIT Entity Type values per RFC 9886.
 *
 * Numeric field of the HHIT DNS resource record.
 *
 * @see https://www.rfc-editor.org/rfc/rfc9886.html#section-6.2.2
 * @see https://www.iana.org/assignments/drip/#hhit-entity-types
 */
typedef enum {
    DRIP_HHIT_ENTITY_TYPE_NOT_DEFINED = 0,
    DRIP_HHIT_ENTITY_TYPE_DIME = 1,
    DRIP_HHIT_ENTITY_TYPE_APEX = 5,
    DRIP_HHIT_ENTITY_TYPE_RAA = 9,
    DRIP_HHIT_ENTITY_TYPE_HDA = 13,
    DRIP_HHIT_ENTITY_TYPE_UA = 16,
    DRIP_HHIT_ENTITY_TYPE_GCS = 17,
    DRIP_HHIT_ENTITY_TYPE_UAS = 18,
    DRIP_HHIT_ENTITY_TYPE_RID_MODULE = 19,
    DRIP_HHIT_ENTITY_TYPE_PILOT = 20,
    DRIP_HHIT_ENTITY_TYPE_OPERATOR = 21,
    DRIP_HHIT_ENTITY_TYPE_DSS = 22,
    DRIP_HHIT_ENTITY_TYPE_USS = 23,
    DRIP_HHIT_ENTITY_TYPE_SP = 24,
    DRIP_HHIT_ENTITY_TYPE_DP = 25,
    DRIP_HHIT_ENTITY_TYPE_SDSP = 26,
    DRIP_HHIT_ENTITY_TYPE_CROWD_SOURCED_RID_FINDER = 27,
} drip_hhit_entity_type_t;

#endif
