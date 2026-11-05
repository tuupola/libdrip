#ifndef DRIP_FORMAT_H
#define DRIP_FORMAT_H

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "drip/error.h"

/**
 * @brief Timestamp epoch, 2019-01-01 00:00:00 UTC as Unix timestamp.
 *
 * @see https://www.rfc-editor.org/rfc/rfc9575.html#section-3.2.4.3
 */
#define DRIP_TIMESTAMP_EPOCH 1546300800

/**
 * @brief Size of a Host Identity in bytes.
 *
 * @see https://www.rfc-editor.org/rfc/rfc9575.html#section-4.2
 */
#define DRIP_HI_SIZE 32

/**
 * @brief Size of a signature in bytes.
 *
 * RFC 9575 defines the field size to be 64 bytes. Algorithm is defined by
 * the HHIT Suite ID (HHSI). The only algorithm which fits to 64 bytes Ed25519
 * i.e. HHSI 5. Not sure how other algorithms should be handled.
 *
 * @see https://www.rfc-editor.org/rfc/rfc9575.html#section-4.1
 */
#define DRIP_SIGNATURE_SIZE 64

/**
 * @brief 32-byte Host Identity (HI).
 *
 * @see https://www.rfc-editor.org/rfc/rfc9575.html#section-4.2
 */
typedef uint8_t drip_hi_t[DRIP_HI_SIZE];

/**
 * @brief 64-byte signature.
 *
 * @see https://www.rfc-editor.org/rfc/rfc9575.html#section-4.1
 */
typedef uint8_t drip_signature_t[DRIP_SIGNATURE_SIZE];

static_assert(sizeof(drip_hi_t) == DRIP_HI_SIZE, "drip_hi_t size mismatch");
static_assert(
    sizeof(drip_signature_t) == DRIP_SIGNATURE_SIZE, "drip_signature_t size mismatch"
);

/**
 * @brief Specific Authentication Method (SAM) Type values per RFC 9575.
 *
 * First byte of SAM Authentication Data. Selects the format of the
 * following authentication data.
 *
 * @see https://www.rfc-editor.org/rfc/rfc9575.html#section-3.2.3
 * @see https://www.iana.org/assignments/drip/#drip-sam-types
 */
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
 * @brief Hierarchical Host Identity Tag (HHIT) Entity Type values per RFC 9886.
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
