#ifndef DRIP_DET_H
#define DRIP_DET_H

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "drip/format.h"
#include "drip/hash.h"

#define DRIP_DET_IPV6_PREFIX_STRING "2001:30::/28"
#define DRIP_DET_IPV6_STRING_SIZE 40

#define DRIP_DET_SIZE 16

typedef uint8_t drip_det_t[DRIP_DET_SIZE];

static_assert(sizeof(drip_det_t) == DRIP_DET_SIZE, "drip_det_t size mismatch");

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
 * Checks the IPv6 prefix, the RAA against the IANA reserved ranges
 * (0..3 and 4000..8191) and the HHIT Suite ID (HHSI). Does not verify the
 * ORCHID hash, use drip_det_verify() for that.
 *
 * @param det Pointer to the DET to validate.
 *
 * @retval DRIP_SUCCESS if det is structurally valid.
 * @retval DRIP_ERROR_NULL_POINTER if det is NULL.
 * @retval DRIP_ERROR_INVALID_IPV6_PREFIX if bytes 0-3 do not match the
 *         2001:30::/28 prefix.
 * @retval DRIP_ERROR_INVALID_RAA if RAA is in an IANA reserved range
 *         (0..3 or 4000..8191).
 * @retval DRIP_ERROR_INVALID_HHSI if HHSI is 0 (RESERVED) or 16.
 *
 * @see https://www.rfc-editor.org/rfc/rfc9374.html#section-3.1
 * @see https://www.rfc-editor.org/rfc/rfc9374.html#section-3.2
 * @see https://www.iana.org/assignments/drip/drip.xhtml#drip-raa
 * @see https://www.rfc-editor.org/rfc/rfc9886.html
 */
int drip_det_validate(const drip_det_t *det);
int drip_det_verify(
    const drip_det_t *det, const drip_hi_t *hi, drip_hash_cb_t callback, void *context
);

/**
 * @brief Render a DET as a canonical IPv6 address string.
 *
 * @param det Pointer to the DET to render.
 * @param buffer Output buffer for the NULL terminated ipv6 string.
 * @param buffer_size Size of the output buffer.
 *
 * @retval DRIP_SUCCESS if the DET was rendered.
 * @retval DRIP_ERROR_NULL_POINTER if det or buffer is NULL.
 * @retval DRIP_ERROR_BUFFER_TOO_SMALL if buffer_size is too small to
 *         hold the rendered ipv6 string.
 */
int drip_det_to_ipv6_string(const drip_det_t *det, char *buffer, size_t buffer_size);

/**
 * @brief Parse a canonical IPv6 address string into a DET.
 *
 * @param det Pointer to the DET that receives the parsed bytes.
 * @param string NULL terminated ipv6 string.
 *
 * @retval DRIP_SUCCESS if the string parsed and is a structurally valid DET.
 * @retval DRIP_ERROR_NULL_POINTER if det or string is NULL.
 * @retval DRIP_ERROR_INVALID_IPV6_STRING if string is not a valid ipv6 address.
 * @retval DRIP_ERROR_INVALID_IPV6_PREFIX if the prefix is outside 2001:30::/28.
 * @retval DRIP_ERROR_INVALID_RAA if the parsed RAA is in an IANA Reserved range
 *         (0..3 or 4000..8191).
 * @retval DRIP_ERROR_INVALID_HHSI if the HHSI is 0 (RESERVED) or 16 (skipped)
 */
int drip_det_from_ipv6_string(drip_det_t *det, const char *string);

/**
 * @brief Encode a DET to its 16-byte wire format.
 *
 * You could also just use `memcpy()` but using this future proofs your
 * code in case the internal representation ever changes.
 *
 * @param det Pointer to the DET to encode.
 * @param buffer Output buffer for the wire format bytes.
 * @param buffer_size Size of @p buffer in bytes. Must be at least DRIP_DET_SIZE.
 *
 * @retval DRIP_SUCCESS on success.
 * @retval DRIP_ERROR_NULL_POINTER if @p det or @p buffer is NULL.
 * @retval DRIP_ERROR_BUFFER_TOO_SMALL if @p buffer_size is less than DRIP_DET_SIZE.
 */
int drip_det_encode(const drip_det_t *det, uint8_t *buffer, size_t buffer_size);

/**
 * @brief Decode and validate a 16-byte buffer into a DET.
 *
 * You could also just use `memcpy()` but using this future proofs your
 * code in case the internal representation ever changes.
 *
 * @param det Pointer to the DET that receives the decoded bytes.
 * @param buffer Input buffer holding the wire format bytes.
 * @param buffer_size Size of @p buffer in bytes. Must be at least DRIP_DET_SIZE.
 *
 * @retval DRIP_SUCCESS on success.
 * @retval DRIP_ERROR_NULL_POINTER if @p det or @p buffer is NULL.
 * @retval DRIP_ERROR_BUFFER_TOO_SMALL if @p buffer_size is less than DRIP_DET_SIZE.
 * @retval DRIP_ERROR_INVALID_IPV6_PREFIX if the decoded prefix is not 2001:30::/28.
 * @retval DRIP_ERROR_INVALID_RAA if the decoded RAA is in an IANA Reserved range
 *         (0..3 or 4000..8191).
 * @retval DRIP_ERROR_INVALID_HHSI if the decoded HHSI is 0 or 16.
 *
 * @see drip_det_validate
 */
int drip_det_decode(drip_det_t *det, const uint8_t *buffer, size_t buffer_size);

#endif /* DRIP_DET_H */
