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

int drip_link_sign(drip_link_t *link, drip_link_sign_cb_t callback, void *context);

int drip_link_verify(drip_link_t *link, drip_link_verify_cb_t callback, void *context);

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
