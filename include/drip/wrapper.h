#ifndef DRIP_WRAPPER_H
#define DRIP_WRAPPER_H

#include <stddef.h>
#include <stdint.h>

#include "drip/det.h"
#include "drip/format.h"

#define DRIP_SAM_TYPE_SIZE 1
#define DRIP_TIMESTAMP_SIZE 4
#define DRIP_WRAPPER_EVIDENCE_SIZE 112
#define DRIP_WRAPPER_EVIDENCE_MAX 4 /* 0..4 messages */
#define DRIP_WRAPPER_MIN_SIZE 89 /* When zero messages. */
#define DRIP_WRAPPER_MAX_SIZE 189 /* When four messages. */

#define RID_MESSAGE_SIZE 25

typedef struct drip_wrapper {
    uint8_t sam_type;

    uint32_t vnb;
    uint32_t vna;

    uint8_t evidence_count; /* Not on the wire. */
    uint8_t evidence[DRIP_WRAPPER_EVIDENCE_MAX][RID_MESSAGE_SIZE];

    drip_det_t det;
    drip_signature_t signature;
} drip_wrapper_t;

/**
 * @brief Callback function type for producing wrapper signatures.
 *
 * Called by drip_wrapper_sign() to perform the actual signing of the payload.
 *
 * @param context Opaque context passed to the callback.
 * @param input Pointer to the payload to sign.
 * @param input_length Length of the payload in bytes.
 * @param buffer Output buffer for the signature.
 * @param buffer_size Size of the signature buffer in bytes.
 * @param output_length Receives resulting wrapper length written.
 *
 * @retval 0 on success.
 * @retval Non-zero on signing failure.
 */
typedef int (*drip_wrapper_sign_cb_t)(
    void *context, const uint8_t *input, size_t input_length, uint8_t *buffer,
    size_t buffer_size, size_t *output_length
);

/**
 * @brief Callback function type for verifying wrapper signatures.
 *
 * Called by drip_wrapper_verify() to perform the actual verification of
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
typedef int (*drip_wrapper_verify_cb_t)(
    void *context, const uint8_t *input, size_t input_length, const uint8_t *signature,
    size_t signature_length
);

int drip_wrapper_init(drip_wrapper_t *wrapper);

/**
 * @brief Set the vnb timestamp.
 *
 * Stored internally as seconds since DRIP_TIMESTAMP_EPOCH.
 *
 * @param wrapper Pointer to the wrapper to modify.
 * @param vnb Offset from DRIP_TIMESTAMP_EPOCH in seconds.
 *
 * @retval DRIP_SUCCESS if vnb was stored.
 * @retval DRIP_ERROR_NULL_POINTER if wrapper is NULL.
 * @retval DRIP_ERROR_OUT_OF_RANGE if vnb > UINT32_MAX - DRIP_TIMESTAMP_EPOCH.
 */
int drip_wrapper_set_vnb(drip_wrapper_t *wrapper, uint32_t vnb);

/**
 * @brief Get the vnb timestamp.
 *
 * Returned as seconds since DRIP_TIMESTAMP_EPOCH.
 *
 * @param wrapper Pointer to the wrapper.
 *
 * @return The vnb timestamp or 0 if wrapper is NULL.
 */
uint32_t drip_wrapper_get_vnb(const drip_wrapper_t *wrapper);

/**
 * @brief Set the vna timestamp.
 *
 * Stored internally as seconds since DRIP_TIMESTAMP_EPOCH.
 *
 * @param wrapper Pointer to the wrapper to modify.
 * @param vna Offset from DRIP_TIMESTAMP_EPOCH in seconds.
 *
 * @retval DRIP_SUCCESS if vna was stored.
 * @retval DRIP_ERROR_NULL_POINTER if wrapper is NULL.
 * @retval DRIP_ERROR_OUT_OF_RANGE if vna > UINT32_MAX - DRIP_TIMESTAMP_EPOCH.
 */
int drip_wrapper_set_vna(drip_wrapper_t *wrapper, uint32_t vna);

/**
 * @brief Get the vna timestamp.
 *
 * Returned as seconds since DRIP_TIMESTAMP_EPOCH.
 *
 * @param wrapper Pointer to the wrapper.
 *
 * @return The vna timestamp or 0 if wrapper is NULL.
 */
uint32_t drip_wrapper_get_vna(const drip_wrapper_t *wrapper);

/**
 * @brief Set the vna from unix timestamp.
 *
 * @param wrapper Pointer to the wrapper to modify.
 * @param unixtime Unix timestamp in seconds.
 *
 * @retval DRIP_SUCCESS if vna was stored.
 * @retval DRIP_ERROR_NULL_POINTER if wrapper is NULL.
 * @retval DRIP_ERROR_OUT_OF_RANGE if unixtime < DRIP_TIMESTAMP_EPOCH.
 */
int drip_wrapper_set_vna_unixtime(drip_wrapper_t *wrapper, uint32_t unixtime);

/**
 * @brief Get the vna as a unix timestamp.
 *
 * @param wrapper Pointer to the wrapper.
 *
 * @return The vna as unix timestamp or 0 if wrapper is NULL.
 */
uint32_t drip_wrapper_get_vna_unixtime(const drip_wrapper_t *wrapper);

/**
 * @brief Set the vnb from unix timestamp.
 *
 * @param wrapper Pointer to the wrapper to modify.
 * @param unixtime Unix timestamp in seconds.
 *
 * @retval DRIP_SUCCESS if vnb was stored.
 * @retval DRIP_ERROR_NULL_POINTER if wrapper is NULL.
 * @retval DRIP_ERROR_OUT_OF_RANGE if unixtime < DRIP_TIMESTAMP_EPOCH.
 */
int drip_wrapper_set_vnb_unixtime(drip_wrapper_t *wrapper, uint32_t unixtime);

/**
 * @brief Get the vnb as a unix timestamp.
 *
 * @param wrapper Pointer to the wrapper.
 *
 * @return The vnb as unix timestamp or 0 if wrapper is NULL.
 */
uint32_t drip_wrapper_get_vnb_unixtime(const drip_wrapper_t *wrapper);

const drip_det_t *drip_wrapper_get_det(const drip_wrapper_t *wrapper);
int drip_wrapper_set_det(drip_wrapper_t *wrapper, const drip_det_t *det);
const drip_signature_t *drip_wrapper_get_signature(const drip_wrapper_t *wrapper);
int drip_wrapper_set_signature(
    drip_wrapper_t *wrapper, const drip_signature_t *signature
);

/**
 * @brief Validate the structural state of a wrapper.
 *
 * Performs structural checks only. Does not verify the signature.
 *
 * @param wrapper Pointer to the wrapper to validate.
 *
 * @retval DRIP_SUCCESS if wrapper is structurally valid.
 * @retval DRIP_ERROR_NULL_POINTER if wrapper is NULL.
 * @retval DRIP_ERROR_INVALID_SAM_TYPE if sam_type is not
 *         DRIP_SAM_TYPE_wrapper.
 * @retval DRIP_ERROR_INVALID_TIMESTAMP if vnb > vna.
 * @retval DRIP_ERROR_ARRAY_OVERFLOW if evidence_count exceeds
 *         DRIP_wrapper_EVIDENCE_MAX.
 * @retval DRIP_ERROR_INVALID_DET if det fails drip_det_validate().
 */
int drip_wrapper_validate(const drip_wrapper_t *wrapper);

/**
 * @brief Get the evidence count.
 *
 * @param wrapper Pointer to the wrapper.
 *
 * @return The evidence count or 0 if wrapper is NULL.
 */
uint8_t drip_wrapper_evidence_count(const drip_wrapper_t *wrapper);

const uint8_t *drip_wrapper_get_evidence_at(const drip_wrapper_t *wrapper, uint8_t index);

int drip_wrapper_add_evidence(
    drip_wrapper_t *wrapper, const uint8_t *buffer, size_t buffer_size
);

/**
 * @brief Sign a wrapper with caller supplied callback.
 *
 * @param wrapper Pointer to the wrapper to be signed.
 * @param callback Callback function used to generate the signature.
 * @param context Opaque context passed to the callback.
 *
 * @pre You must call drip_wrapper_update_current_hash() atleast once
 *      before calling this function.
 *
 * @retval DRIP_SUCCESS if signing succeeded.
 * @retval DRIP_ERROR_NULL_POINTER if wrapper or callback is NULL.
 * @retval DRIP_ERROR_CALLBACK_FAILED if callback returned non-zero.
 */
int drip_wrapper_sign(
    drip_wrapper_t *wrapper, drip_wrapper_sign_cb_t callback, void *context
);

int drip_wrapper_verify(
    drip_wrapper_t *wrapper, drip_wrapper_verify_cb_t callback, void *context
);

int drip_wrapper_encode(
    const drip_wrapper_t *wrapper, uint8_t *buffer, size_t buffer_size,
    size_t *encoded_length
);

/**
 * @brief Decode a wrapper from its wire format.
 *
 * The buffer must contain only the bytes for the wrapper and nothing else.
 *
 * @param wrapper Pointer to the wrapper that receives the decoded data.
 * @param buffer Input buffer holding the wire format bytes.
 * @param buffer_size Size of buffer in bytes.
 *
 * @retval DRIP_SUCCESS on success.
 * @retval DRIP_ERROR_NULL_POINTER if wrapper or buffer is NULL.
 * @retval DRIP_ERROR_BUFFER_TOO_SMALL if buffer_size is less than DRIP_WRAPPER_MIN_SIZE.
 * @retval DRIP_ERROR_INVALID_LENGTH if the evidence payload length is not a multiple of DRIP_HASH_SIZE.
 * @retval DRIP_ERROR_ARRAY_OVERFLOW if the evidence count would exceed DRIP_wrapper_EVIDENCE_MAX.
 * @retval DRIP_ERROR_INVALID_SAM_TYPE if the decoded SAM type is not DRIP_SAM_TYPE_WRAPPER.
 */
int drip_wrapper_decode(
    drip_wrapper_t *wrapper, const uint8_t *buffer, size_t buffer_size
);

/**
 * @brief Serialize a DRIP wrapper to a JSON string.
 *
 * On success writes a NULL terminated JSON to buffer. When buffer_size is
 * too small the output is truncated and DRIP_ERROR_BUFFER_TOO_SMALL is returned.
 * The truncated buffer is still NULL terminated.
 *
 * @param link Pointer to the wrapper to serialize.
 * @param buffer Output buffer for the JSON representation.
 * @param buffer_size Size of buffer in bytes.
 * @param json_length Optional. Receives receives the number of characters
 *        for the full non truncated output. Ignored if NULL.
 *
 * @retval DRIP_SUCCESS on success.
 * @retval DRIP_ERROR_NULL_POINTER if link or buffer is NULL.
 * @retval DRIP_ERROR_BUFFER_TOO_SMALL if buffer_size is too small.
 */
int drip_wrapper_to_json(
    const drip_wrapper_t *wrapper, char *buffer, size_t buffer_size, size_t *json_length
);

#endif /* DRIP_WRAPPER_H */
