#ifndef DRIP_MANIFEST_H
#define DRIP_MANIFEST_H

#include <stddef.h>
#include <stdint.h>

#include "drip/format.h"
#include "drip/hash.h"

#define DRIP_SAM_TYPE_SIZE 1
#define DRIP_TIMESTAMP_SIZE 4
#define DRIP_EVIDENCE_SIZE 112
#define DRIP_DET_SIZE 16
#define DRIP_SIGNATURE_SIZE 64
#define DRIP_MANIFEST_EVIDENCE_MAX 11

#define DRIP_MANIFEST_MIN_SIZE 113 /* when zero hashes */
#define DRIP_MANIFEST_MAX_SIZE 201 /* when 11 hashes */

/** @brief Timestamp epoch (2019-01-01 00:00:00 UTC as Unix timestamp). */
#define DRIP_MANIFEST_TIMESTAMP_EPOCH 1546300800

typedef uint8_t drip_det_t[DRIP_DET_SIZE];
typedef uint8_t drip_sig_t[DRIP_SIGNATURE_SIZE];

typedef struct drip_manifest {
    uint8_t sam_type;

    uint32_t vnb;
    uint32_t vna;

    drip_hash_t previous_hash;
    drip_hash_t current_manifest_hash;
    drip_hash_t link_hash;

    uint8_t evidence_count;
    drip_hash_t evidence[DRIP_MANIFEST_EVIDENCE_MAX];

    drip_det_t det;
    drip_sig_t signature;
} drip_manifest_t;

/**
 * @brief Callback function type for producing manifest signatures.
 *
 * Called by drip_manifest_sign() to perform the actual signing of the payload.
 *
 * @param context Opaque context passed to the callback.
 * @param input Pointer to the payload to sign.
 * @param input_length Length of the payload in bytes.
 * @param signature Output buffer for the signature.
 * @param signature_size Size of the signature buffer in bytes.
 * @param signature_length Output: actual signature length written.
 *
 * @retval 0 on success.
 * @retval Non-zero on signing failure.
 */
typedef int (*drid_manifest_sign_cb_t)(
    void *context,
    const uint8_t *input,
    size_t input_length,
    uint8_t *signature,
    size_t signature_size,
    size_t *signature_length
);

/**
 * @brief Callback function type for verifying manifest signatures.
 *
 * Called by drip_manifest_verify() to perform the actual verification of
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
typedef int (*rid_manifest_verify_cb_t)(
    void *context,
    const uint8_t *input,
    size_t input_length,
    const uint8_t *signature,
    size_t signature_length
);

int drip_manifest_init(drip_manifest_t *manifest);

uint32_t drip_manifest_get_vnb(const drip_manifest_t *manifest);
int drip_manifest_set_vnb(drip_manifest_t *manifest, uint32_t vnb);

uint32_t drip_manifest_get_vna(const drip_manifest_t *manifest);
int drip_manifest_set_vna(drip_manifest_t *manifest, uint32_t vna);

int drip_manifest_set_vna_unixtime(drip_manifest_t *manifest, uint32_t unixtime);
uint32_t drip_manifest_get_vna_unixtime(const drip_manifest_t *manifest);

int drip_manifest_set_vnb_unixtime(drip_manifest_t *manifest, uint32_t unixtime);
uint32_t drip_manifest_get_vnb_unixtime(const drip_manifest_t *manifest);

int drip_manifest_get_previous_hash(const drip_manifest_t *manifest, drip_hash_t *hash);
int drip_manifest_set_previous_hash(drip_manifest_t *manifest, const drip_hash_t *hash);

int drip_manifest_get_current_hash(const drip_manifest_t *manifest, drip_hash_t *hash);
int drip_manifest_set_current_hash(drip_manifest_t *manifest, const drip_hash_t *hash);

int drip_manifest_get_link_hash(const drip_manifest_t *manifest, drip_hash_t *hash);
int drip_manifest_set_link_hash(drip_manifest_t *manifest, const drip_hash_t *hash);

int drip_manifest_get_det(const drip_manifest_t *manifest, drip_det_t *det);
int drip_manifest_set_det(drip_manifest_t *manifest, const drip_det_t *det);

int drip_manifest_get_signature(const drip_manifest_t *manifest, drip_sig_t *signature);
int drip_manifest_set_signature(drip_manifest_t *manifest, const drip_sig_t *signature);

int drip_manifest_add_evidence(drip_manifest_t *manifest, const drip_hash_t *hash);
int drip_manifest_get_evidence_at(const drip_manifest_t *manifest, uint8_t index, drip_hash_t *hash);

/**
 * @brief Sign a DRIP manifest with caller supplied callback.
 *
 * @param auth Pointer to the DRIP Manifest to be signed.
 * @param callback Callback function used to produce the signature.
 * @param context Opaque context passed to the callback.
 *
 * @retval DRIP_SUCCESS if signing succeeded.
 * @retval DRIP_ERROR_NULL_POINTER if auth, message, or callback is NULL.
 */
int drip_manifest_sign(
    drip_manifest_t *manifest,
    drid_manifest_sign_cb_t callback,
    void *context
);

int drip_manifest_verify(
    drip_manifest_t *manifest,
    rid_manifest_verify_cb_t callback,
    void *context
);

int drip_manifest_encode(
    const drip_manifest_t *manifest,
    uint8_t *buffer,
    size_t buffer_size,
    size_t *encoded_length
);

int drip_manifest_decode(
    drip_manifest_t *manifest,
    const uint8_t *buffer,
    size_t buffer_size
);

int drip_manifest_to_json(
    const drip_manifest_t *manifest,
    char *buffer,
    size_t buffer_size
);

#endif
