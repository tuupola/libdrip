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
 * @param output_length Receives resulting signature length written.
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

/**
 * @brief Initialize a wrapper.
 *
 * Zeroes the wrapper and sets sam_type to DRIP_SAM_TYPE_WRAPPER.
 *
 * @param wrapper Pointer to the wrapper to initialize.
 *
 * @retval DRIP_SUCCESS if the wrapper was initialized.
 * @retval DRIP_ERROR_NULL_POINTER if wrapper is NULL.
 */
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

/**
 * @brief Get the DET.
 *
 * @param wrapper Pointer to the wrapper.
 *
 * @return Pointer to the stored DET or NULL if wrapper is NULL.
 */
const drip_det_t *drip_wrapper_get_det(const drip_wrapper_t *wrapper);

/**
 * @brief Set the DET.
 *
 * @param wrapper Pointer to the wrapper to modify.
 * @param det Pointer to the DET to store.
 *
 * @retval DRIP_SUCCESS if the DET was stored.
 * @retval DRIP_ERROR_NULL_POINTER if wrapper or det is NULL.
 */
int drip_wrapper_set_det(drip_wrapper_t *wrapper, const drip_det_t *det);

/**
 * @brief Get the signature.
 *
 * @param wrapper Pointer to the wrapper.
 *
 * @return Pointer to the stored signature or NULL if wrapper is NULL.
 */
const drip_signature_t *drip_wrapper_get_signature(const drip_wrapper_t *wrapper);

/**
 * @brief Set the signature.
 *
 * @param wrapper Pointer to the wrapper to modify.
 * @param signature Pointer to the signature to store.
 *
 * @retval DRIP_SUCCESS if the signature was stored.
 * @retval DRIP_ERROR_NULL_POINTER if wrapper or signature is NULL.
 */
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
 * @retval DRIP_ERROR_INVALID_SAM_TYPE if sam_type is not DRIP_SAM_TYPE_WRAPPER.
 * @retval DRIP_ERROR_INVALID_TIMESTAMP if vnb > vna.
 * @retval DRIP_ERROR_ARRAY_OVERFLOW if evidence_count exceeds DRIP_WRAPPER_EVIDENCE_MAX.
 * @retval DRIP_ERROR_INVALID_MESSAGE_TYPE if an evidence message type is not
 *         0x0 0x1 0x3 0x4 or 0x5.
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

/**
 * @brief Get evidence at the given index.
 *
 * @param wrapper Pointer to the wrapper.
 * @param index Zero-based evidence index.
 *
 * @return Pointer to the stored 25-byte message or NULL if wrapper is NULL
 *         or index >= evidence_count.
 */
const uint8_t *drip_wrapper_get_evidence_at(const drip_wrapper_t *wrapper, uint8_t index);

/**
 * @brief Add a 25-byte ASTM message to the wrapper evidence.
 *
 * Only ASTM Message Types 0x0 0x1 0x3 0x4 and 0x5 are allowed.
 *
 * @param wrapper Pointer to the wrapper to modify.
 * @param buffer Pointer to a 25-byte ASTM message.
 * @param buffer_size Size of buffer in bytes. Must be RID_MESSAGE_SIZE.
 *
 * @retval DRIP_SUCCESS if the message was added to the wrapper.
 * @retval DRIP_ERROR_NULL_POINTER if wrapper or buffer is NULL.
 * @retval DRIP_ERROR_INVALID_LENGTH if buffer_size is not RID_MESSAGE_SIZE.
 * @retval DRIP_ERROR_INVALID_MESSAGE_TYPE if the given ASTM message type is not allowed.
 * @retval DRIP_ERROR_ARRAY_OVERFLOW if evidence_count would exceed
 *         DRIP_WRAPPER_EVIDENCE_MAX.
 *
 * @see https://www.rfc-editor.org/rfc/rfc9575.html#section-4.3
 */
int drip_wrapper_add_evidence(
    drip_wrapper_t *wrapper, const uint8_t *buffer, size_t buffer_size
);

/**
 * @brief Sign a wrapper with caller supplied callback.
 *
 * Validates the wrapper with drip_wrapper_validate() before signing.
 * The callback is not called if validation fails.
 *
 * @param wrapper Pointer to the wrapper to be signed.
 * @param callback Callback function used to generate the signature.
 * @param context Opaque context passed to the callback.
 *
 * @retval DRIP_SUCCESS if signing succeeded.
 * @retval DRIP_ERROR_NULL_POINTER if wrapper or callback is NULL.
 * @retval DRIP_ERROR_INVALID_SAM_TYPE if sam_type is not DRIP_SAM_TYPE_WRAPPER.
 * @retval DRIP_ERROR_INVALID_TIMESTAMP if vnb > vna.
 * @retval DRIP_ERROR_ARRAY_OVERFLOW if evidence_count exceeds DRIP_WRAPPER_EVIDENCE_MAX.
 * @retval DRIP_ERROR_INVALID_MESSAGE_TYPE if an evidence message type is not
 *         0x0 0x1 0x3 0x4 or 0x5.
 * @retval DRIP_ERROR_INVALID_DET if det fails drip_det_validate().
 * @retval DRIP_ERROR_CALLBACK_FAILED if callback returned non-zero.
 * @retval DRIP_ERROR_INVALID_LENGTH if the signature is not DRIP_SIGNATURE_SIZE.
 */
int drip_wrapper_sign(
    drip_wrapper_t *wrapper, drip_wrapper_sign_cb_t callback, void *context
);

/**
 * @brief Verify a wrapper with caller supplied callback.
 *
 * Validates the wrapper with drip_wrapper_validate() before verifying.
 * The callback is not called if validation or the time window check fails.
 *
 * @param wrapper Pointer to the wrapper to be verified.
 * @param unixtime Unix time in seconds or 0 to ignore.
 * @param callback Callback function used to verify the signature.
 * @param context Opaque context passed to the callback.
 *
 * @retval DRIP_SUCCESS if verification succeeded.
 * @retval DRIP_ERROR_NULL_POINTER if wrapper or callback is NULL.
 * @retval DRIP_ERROR_INVALID_SAM_TYPE if sam_type is not DRIP_SAM_TYPE_WRAPPER.
 * @retval DRIP_ERROR_INVALID_TIMESTAMP if vnb > vna.
 * @retval DRIP_ERROR_ARRAY_OVERFLOW if evidence_count exceeds DRIP_WRAPPER_EVIDENCE_MAX.
 * @retval DRIP_ERROR_INVALID_MESSAGE_TYPE if an evidence message type is not
 *         0x0 0x1 0x3 0x4 or 0x5.
 * @retval DRIP_ERROR_INVALID_DET if det fails drip_det_validate().
 * @retval DRIP_ERROR_TIMESTAMP_NOT_YET_VALID if unixtime is before vnb.
 * @retval DRIP_ERROR_TIMESTAMP_EXPIRED if unixtime is after vna.
 * @retval DRIP_ERROR_CALLBACK_FAILED if callback returned non-zero.
 */
int drip_wrapper_verify(
    const drip_wrapper_t *wrapper, uint32_t unixtime, drip_wrapper_verify_cb_t callback,
    void *context
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
 * @retval DRIP_ERROR_INVALID_LENGTH if the evidence payload length is not a multiple of RID_MESSAGE_SIZE.
 * @retval DRIP_ERROR_ARRAY_OVERFLOW if the evidence count would exceed DRIP_WRAPPER_EVIDENCE_MAX.
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
 * @param wrapper Pointer to the wrapper to serialize.
 * @param buffer Output buffer for the JSON representation.
 * @param buffer_size Size of buffer in bytes.
 * @param json_length Optional. Receives the number of characters
 *        for the full non truncated output. Ignored if NULL.
 *
 * @retval DRIP_SUCCESS on success.
 * @retval DRIP_ERROR_NULL_POINTER if wrapper or buffer is NULL.
 * @retval DRIP_ERROR_BUFFER_TOO_SMALL if buffer_size is too small.
 */
int drip_wrapper_to_json(
    const drip_wrapper_t *wrapper, char *buffer, size_t buffer_size, size_t *json_length
);

#endif /* DRIP_WRAPPER_H */
