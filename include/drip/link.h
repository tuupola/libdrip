#ifndef DRIP_LINK_H
#define DRIP_LINK_H

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "drip/det.h"
#include "drip/format.h"

#define DRIP_LINK_SIZE 137

/**
 * @brief Callback function type for producing link signatures.
 *
 * Called by drip_link_sign() to perform the actual signing of the payload.
 *
 * @param context Opaque context passed to the callback.
 * @param input Pointer to the payload to sign.
 * @param input_length Length of the payload in bytes.
 * @param buffer Output buffer for the signature.
 * @param buffer_size Size of the signature buffer in bytes.
 * @param output_length Receives resulting link length written.
 *
 * @retval 0 on success.
 * @retval Non-zero on signing failure.
 */
typedef int (*drip_link_sign_cb_t)(
    void *context, const uint8_t *input, size_t input_length, uint8_t *buffer,
    size_t buffer_size, size_t *output_length
);

/**
 * @brief Callback function type for verifying link signatures.
 *
 * Called by drip_link_verify() to perform the actual verification of
 * the signed payload.
 *
 * @param context Opaque context passed to the callback.
 * @param input Pointer to the signed payload data.
 * @param input_length Length of the signed payload in bytes.
 * @param signature Pointer to the signature to verify against.
 * @param signature_length Length of the signature in bytes.
 *
 * @retval 0 on success.
 * @retval Non-zero on verification failure.
 */
typedef int (*drip_link_verify_cb_t)(
    void *context, const uint8_t *input, size_t input_length, const uint8_t *signature,
    size_t signature_length
);

typedef struct __attribute__((__packed__)) drip_link {
    uint8_t sam_type;

    uint32_t vnb;
    uint32_t vna;

    drip_det_t child_det;
    drip_hi_t child_hi;
    drip_det_t parent_det;

    drip_signature_t signature;
} drip_link_t;

static_assert(sizeof(drip_link_t) == DRIP_LINK_SIZE, "drip_link_t size mismatch");

int drip_link_init(drip_link_t *link);

/**
 * @brief Set the vnb timestamp.
 *
 * Stored internally as seconds since DRIP_TIMESTAMP_EPOCH.
 *
 * @param link Pointer to the link to modify.
 * @param vnb Offset from DRIP_TIMESTAMP_EPOCH in seconds.
 *
 * @retval DRIP_SUCCESS if vnb was stored.
 * @retval DRIP_ERROR_NULL_POINTER if link is NULL.
 * @retval DRIP_ERROR_OUT_OF_RANGE if vnb > UINT32_MAX - DRIP_TIMESTAMP_EPOCH.
 */
int drip_link_set_vnb(drip_link_t *link, uint32_t vnb);

/**
 * @brief Get the vnb timestamp.
 *
 * Returned as seconds since DRIP_TIMESTAMP_EPOCH.
 *
 * @param link Pointer to the link.
 *
 * @return The stored vnb, or 0 if link is NULL.
 */
uint32_t drip_link_get_vnb(const drip_link_t *link);

/**
 * @brief Set the vna timestamp.
 *
 * Stored internally as seconds since DRIP_TIMESTAMP_EPOCH.
 *
 * @param link Pointer to the link to modify.
 * @param vna Offset from DRIP_TIMESTAMP_EPOCH in seconds.
 *
 * @retval DRIP_SUCCESS if vna was stored.
 * @retval DRIP_ERROR_NULL_POINTER if link is NULL.
 * @retval DRIP_ERROR_OUT_OF_RANGE if vna > UINT32_MAX - DRIP_TIMESTAMP_EPOCH.
 */
int drip_link_set_vna(drip_link_t *link, uint32_t vna);

/**
 * @brief Get the vna timestamp.
 *
 * Returned as seconds since DRIP_TIMESTAMP_EPOCH.
 *
 * @param link Pointer to the link.
 *
 * @return The stored vna, or 0 if link is NULL.
 */
uint32_t drip_link_get_vna(const drip_link_t *link);

/**
 * @brief Set the vna from unix timestamp.
 *
 * @param link Pointer to the link to modify.
 * @param unixtime Unix timestamp in seconds.
 *
 * @retval DRIP_SUCCESS if vna was stored.
 * @retval DRIP_ERROR_NULL_POINTER if link is NULL.
 * @retval DRIP_ERROR_OUT_OF_RANGE if unixtime < DRIP_TIMESTAMP_EPOCH.
 */
int drip_link_set_vna_unixtime(drip_link_t *link, uint32_t unixtime);

/**
 * @brief Get the vna timestamp.
 *
 * Returned as seconds since DRIP_TIMESTAMP_EPOCH.
 *
 * @param manifest Pointer to the manifest.
 *
 * @return The vna timestamp or 0 if manifest is NULL.
 */
uint32_t drip_link_get_vna_unixtime(const drip_link_t *link);

/**
 * @brief Set the vnb from unix timestamp.
 *
 * @param link Pointer to the link to modify.
 * @param unixtime Unix timestamp in seconds.
 *
 * @retval DRIP_SUCCESS if vnb was stored.
 * @retval DRIP_ERROR_NULL_POINTER if link is NULL.
 * @retval DRIP_ERROR_OUT_OF_RANGE if unixtime < DRIP_TIMESTAMP_EPOCH.
 */
int drip_link_set_vnb_unixtime(drip_link_t *link, uint32_t unixtime);

/**
 * @brief Get the vnb timestamp.
 *
 * Returned as seconds since DRIP_TIMESTAMP_EPOCH.
 *
 * @param manifest Pointer to the manifest.
 *
 * @return The vnb timestamp or 0 if manifest is NULL.
 */
uint32_t drip_link_get_vnb_unixtime(const drip_link_t *link);

const drip_det_t *drip_link_get_child_det(const drip_link_t *link);
int drip_link_set_child_det(drip_link_t *link, const drip_det_t *det);

const drip_hi_t *drip_link_get_child_hi(const drip_link_t *link);
int drip_link_set_child_hi(drip_link_t *link, const drip_hi_t *hi);

const drip_det_t *drip_link_get_parent_det(const drip_link_t *link);
int drip_link_set_parent_det(drip_link_t *link, const drip_det_t *det);

const drip_signature_t *drip_link_get_signature(const drip_link_t *link);
int drip_link_set_signature(drip_link_t *link, const drip_signature_t *signature);

int drip_link_validate(const drip_link_t *link);

int drip_link_decode(drip_link_t *link, const uint8_t *buffer, size_t buffer_size);
int drip_link_encode(
    const drip_link_t *link, uint8_t *buffer, size_t buffer_size, size_t *encoded_length
);

/**
 * @brief Sign a Link.
 *
 * Signs the Link using the provided callback and parent private key. Pass
 * the private key in the context.
 *
 * @code
 * int rc = drip_link_sign(&link, sign_ed25519, (void *)secret_key);
 * @endcode
 *
 * @param link Pointer to the Link to sign.
 * @param callback Callback function used to generate the signature.
 * @param context Opaque context passed to the callback.
 *
 * @retval DRIP_SUCCESS if the Link was signed.
 * @retval DRIP_ERROR_NULL_POINTER if link or callback is NULL.
 * @retval DRIP_ERROR_CALLBACK_FAILED if callback returned an error.
 * @retval DRIP_ERROR_INVALID_LENGTH if the signature is not DRIP_SIGNATURE_SIZE.
 *
 * @see https://www.rfc-editor.org/rfc/rfc9575.html#section-4.2
 */
int drip_link_sign(drip_link_t *link, drip_link_sign_cb_t callback, void *context);

/**
 * @brief Verify the signature of a Link.
 *
 * Verifies the signature using the provided callback and parent HI. Parent HI
 * is the public key, pass it in the context.
 *
 * @code
 * const drip_hi_t *parent_hi = drip_link_get_child_hi(&parent_link);
 * int rc = drip_link_verify(&child_link, verify_ed25519, (void *)parent_hi);
 * @endcode
 *
 * @param link Pointer to the Link to verify.
 * @param callback Callback function used to verify the signature.
 * @param context Opaque context passed to the callback.
 *
 * @retval DRIP_SUCCESS if the signature verifies.
 * @retval DRIP_ERROR_NULL_POINTER if link or callback is NULL.
 * @retval DRIP_ERROR_CALLBACK_FAILED if callback returned an error.
 *
 * @see https://www.rfc-editor.org/rfc/rfc9575.html#section-4.2
 */
int drip_link_verify(const drip_link_t *link, drip_link_verify_cb_t callback, void *context);

/**
 * @brief Verify a chain of Links from a trusted root.
 *
 * @param link_array Array of Links.
 * @param link_count Number of Links in link_array.
 * @param root_det Trusted root DET.
 * @param root_hi Trusted root Host Identity.
 * @param unixtime Unix time in seconds or 0 to skip the VNB/VNA check.
 * @param hash_cb Callback used to verify each child DET hash.
 * @param verify_cb Callback used to verify each Link signature.
 *
 * @retval DRIP_SUCCESS if the chain verifies.
 * @retval DRIP_ERROR_NULL_POINTER if link_array, root_det, root_hi, hash_cb,
 *         or verify_cb is NULL.
 * @retval DRIP_ERROR_INVALID_TIMESTAMP if unixtime is outside a hop VNB/VNA window.
 * @retval DRIP_ERROR_CALLBACK_FAILED if a callback returned am error.
 * @retval DRIP_ERROR_VERIFICATION_FAILED if a hop DET hash or signature
 *         does not match or the chain is broken.
 *
 * @see https://www.rfc-editor.org/rfc/rfc9575.html#section-3.1.2
 * @see https://www.rfc-editor.org/rfc/rfc9575.html#section-4.2
 */
int drip_link_verify_chain(
    const drip_link_t *link_array, size_t link_count, const drip_det_t *root_det,
    const drip_hi_t *root_hi, uint32_t unixtime, drip_hash_cb_t hash_cb,
    drip_link_verify_cb_t verify_cb
);

/**
 * @brief Serialize a DRIP link to a JSON string.
 *
 * On success writes a NULL terminated JSON to @p buffer. When @p buffer_size is
 * too small the output is truncated and DRIP_ERROR_BUFFER_TOO_SMALL is returned.
 * The truncated buffer is still NULL terminated.
 *
 * @param link Pointer to the link to serialize.
 * @param buffer Output buffer for the JSON representation.
 * @param buffer_size Size of @p buffer in bytes.
 * @param json_length Optional. Receives receives the number of characters
 *                    for the full non truncated output. Ignored if NULL.
 *
 * @retval DRIP_SUCCESS on success.
 * @retval DRIP_ERROR_NULL_POINTER if @p link or @p buffer is NULL.
 * @retval DRIP_ERROR_BUFFER_TOO_SMALL if @p buffer_size is too small.
 */
int drip_link_to_json(
    const drip_link_t *link, char *buffer, size_t buffer_size, size_t *json_length
);

#endif /* DRIP_LINK_H */
