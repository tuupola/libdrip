#ifndef DRIP_DET_H
#define DRIP_DET_H

#include <stddef.h>
#include <stdint.h>

#include "drip/format.h"
#include "drip/hash.h"

#define DRIP_DET_IPV6_PREFIX_STRING "2001:30::/28"
#define DRIP_DET_IPV6_STRING_SIZE 40

#define DRIP_DET_SIZE 16

typedef uint8_t drip_det_t[DRIP_DET_SIZE];

/**
 * @brief HHIT Suite ID (HHSI) values per RFC 9374.
 *
 * Identifies the hash and signature algorithms used by a DET.
 * Values 0 (RESERVED) and 16 (skipped) must not be used.
 *
 * @see https://www.rfc-editor.org/rfc/rfc9374.html#section-3.2
 */
typedef enum {
    DRIP_HHSI_RESERVED = 0,
    DRIP_HHSI_RSA_DSA_SHA256 = 1,
    DRIP_HHSI_ECDSA_SHA384 = 2,
    DRIP_HHSI_ECDSA_LOW_SHA1 = 3,
    DRIP_HHSI_EDDSA_CSHAKE128 = 5,
    DRIP_HHSI_HDA_PRIVATE_USE_1 = 254,
    DRIP_HHSI_HDA_PRIVATE_USE_2 = 255,
} drip_hhsi_t;

int drip_det_init(drip_det_t *det);

int drip_det_set_raa(drip_det_t *det, uint16_t raa);
uint16_t drip_det_get_raa(const drip_det_t *det);

int drip_det_set_hda(drip_det_t *det, uint16_t hda);
uint16_t drip_det_get_hda(const drip_det_t *det);

int drip_det_set_hid(drip_det_t *det, uint32_t hid);
uint32_t drip_det_get_hid(const drip_det_t *det);

/**
 * @brief Set the HHIT Suite ID (HHSI) of a DET.
 *
 * Values 0 (RESERVED) and 16 are invalid per RFC 9374 §3.2.
 *
 * @param det Pointer to the DET to modify.
 * @param hhsi HHIT Suite ID to store.
 *
 * @retval DRIP_SUCCESS if the HHSI was stored.
 * @retval DRIP_ERROR_NULL_POINTER if det is NULL.
 * @retval DRIP_ERROR_INVALID_HHSI if hhsi is 0 (RESERVED) or 16.
 *
 * @see https://www.rfc-editor.org/rfc/rfc9374.html#section-3.2
 */
int drip_det_set_hhsi(drip_det_t *det, drip_hhsi_t hhsi);
uint8_t drip_det_get_hhsi(const drip_det_t *det);

int drip_det_set_hash(drip_det_t *det, const drip_hash_t *hash);
const drip_hash_t *drip_det_get_hash(const drip_det_t *det);
int drip_det_update_hash(
    drip_det_t *det, const drip_hi_t *hi, drip_hash_cb_t callback, void *context
);

/**
 * @brief Validate the structural integrity of a DET.
 *
 * Checks the IPv6 prefix and the HHIT Suite ID (HHSI). Does not
 * verify the ORCHID hash, use drip_det_verify() for that.
 *
 * @param det Pointer to the DET to validate.
 *
 * @retval DRIP_SUCCESS if det is structurally valid.
 * @retval DRIP_ERROR_NULL_POINTER if det is NULL.
 * @retval DRIP_ERROR_INVALID_IPV6_PREFIX if bytes 0-3 do not match the 2001:30::/28 prefix.
 * @retval DRIP_ERROR_INVALID_HHSI if HHSI is 0 (RESERVED) or 16.
 *
 * @see https://www.rfc-editor.org/rfc/rfc9374.html#section-3.1
 * @see https://www.rfc-editor.org/rfc/rfc9374.html#section-3.2
 */
int drip_det_validate(const drip_det_t *det);
int drip_det_verify(
    const drip_det_t *det, const drip_hi_t *hi, drip_hash_cb_t callback, void *context
);

// int drip_det_to_ipv6_string(const drip_det_t *det, char *buffer, size_t buffer_size);
// int drip_det_from_ipv6_string(drip_det_t *det, const char *string);

#endif /* DRIP_DET_H */
