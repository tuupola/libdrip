#include <string.h>

#include "drip/manifest.h"

int drip_manifest_init(drip_manifest_t *manifest) {
    if (manifest == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    memset(manifest, 0, sizeof(drip_manifest_t));
    manifest->sam_type = DRIP_SAM_TYPE_MANIFEST;

    return DRIP_SUCCESS;
}

uint32_t drip_manifest_get_vnb(const drip_manifest_t *manifest) {
    if (manifest == NULL) {
        return 0;
    }
    return manifest->vnb;
}

int drip_manifest_set_vnb(drip_manifest_t *manifest, uint32_t vnb) {
    if (manifest == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    manifest->vnb = vnb;
    return DRIP_SUCCESS;
}

int drip_manifest_set_vnb_unixtime(drip_manifest_t *manifest, uint32_t unixtime) {
    if (manifest == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    manifest->vnb = unixtime - DRIP_MANIFEST_TIMESTAMP_EPOCH;

    return DRIP_SUCCESS;
}

uint32_t drip_manifest_get_vnb_unixtime(const drip_manifest_t *manifest) {
    if (NULL == manifest) {
        return 0;
    }

    return manifest->vnb + DRIP_MANIFEST_TIMESTAMP_EPOCH;
}

int drip_manifest_set_vna_unixtime(drip_manifest_t *manifest, uint32_t unixtime) {
    if (manifest == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    manifest->vna = unixtime - DRIP_MANIFEST_TIMESTAMP_EPOCH;
    return DRIP_SUCCESS;
}

uint32_t drip_manifest_get_vna_unixtime(const drip_manifest_t *manifest) {
    if (manifest == NULL) {
        return 0;
    }
    return manifest->vna + DRIP_MANIFEST_TIMESTAMP_EPOCH;
}

uint32_t drip_manifest_get_vna(const drip_manifest_t *manifest) {
    if (manifest == NULL) {
        return 0;
    }
    return manifest->vna;
}

int drip_manifest_set_vna(drip_manifest_t *manifest, uint32_t vna) {
    if (manifest == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    manifest->vna = vna;
    return DRIP_SUCCESS;
}

int drip_manifest_get_previous_manifest_hash(const drip_manifest_t *manifest, drip_hash_t *hash) {
    if (manifest == NULL || hash == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    memcpy(hash, manifest->previous_manifest_hash, sizeof(drip_hash_t));
    return DRIP_SUCCESS;
}

int drip_manifest_set_previous_manifest_hash(drip_manifest_t *manifest, const drip_hash_t *hash) {
    if (manifest == NULL || hash == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    memcpy(manifest->previous_manifest_hash, hash, sizeof(drip_hash_t));
    return DRIP_SUCCESS;
}

int drip_manifest_get_current_manifest_hash(const drip_manifest_t *manifest, drip_hash_t *hash) {
    if (manifest == NULL || hash == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    memcpy(hash, manifest->current_manifest_hash, sizeof(drip_hash_t));
    return DRIP_SUCCESS;
}

int drip_manifest_set_current_manifest_hash(drip_manifest_t *manifest, const drip_hash_t *hash) {
    if (manifest == NULL || hash == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    memcpy(manifest->current_manifest_hash, hash, sizeof(drip_hash_t));
    return DRIP_SUCCESS;
}

int drip_manifest_get_drip_link_hash(const drip_manifest_t *manifest, drip_hash_t *hash) {
    if (manifest == NULL || hash == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    memcpy(hash, manifest->drip_link_hash, sizeof(drip_hash_t));
    return DRIP_SUCCESS;
}

int drip_manifest_set_drip_link_hash(drip_manifest_t *manifest, const drip_hash_t *hash) {
    if (manifest == NULL || hash == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    memcpy(manifest->drip_link_hash, hash, sizeof(drip_hash_t));
    return DRIP_SUCCESS;
}

int drip_manifest_get_det(const drip_manifest_t *manifest, drip_det_t *det) {
    if (manifest == NULL || det == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    memcpy(det, manifest->det, sizeof(drip_det_t));
    return DRIP_SUCCESS;
}

int drip_manifest_set_det(drip_manifest_t *manifest, const drip_det_t *det) {
    if (manifest == NULL || det == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    memcpy(manifest->det, det, sizeof(drip_det_t));
    return DRIP_SUCCESS;
}

int drip_manifest_get_signature(const drip_manifest_t *manifest, drip_sig_t *signature) {
    if (manifest == NULL || signature == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    memcpy(signature, manifest->signature, sizeof(drip_sig_t));
    return DRIP_SUCCESS;
}

int drip_manifest_set_signature(drip_manifest_t *manifest, const drip_sig_t *signature) {
    if (manifest == NULL || signature == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    memcpy(manifest->signature, signature, sizeof(drip_sig_t));
    return DRIP_SUCCESS;
}

int drip_manifest_add_message_hash(drip_manifest_t *manifest, const drip_hash_t *hash) {
    if (manifest == NULL || hash == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    if (manifest->message_hash_count >= DRIP_MANIFEST_MESSAGES_MAX) {
        return DRIP_ERROR_ARRAY_FULL;
    }
    memcpy(manifest->evidence[manifest->message_hash_count], hash, sizeof(drip_hash_t));
    manifest->message_hash_count++;
    return DRIP_SUCCESS;
}

int drip_manifest_get_message_hash_at(const drip_manifest_t *manifest, uint8_t index, drip_hash_t *hash) {
    if (manifest == NULL || hash == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    if (index >= manifest->message_hash_count) {
        return DRIP_ERROR_INVALID_INDEX;
    }
    memcpy(hash, manifest->evidence[index], sizeof(drip_hash_t));
    return DRIP_SUCCESS;
}

int drip_manifest_sign(
    drip_manifest_t *manifest,
    drid_manifest_sign_cb_t callback,
    void *context
) {
    if (manifest == NULL || callback == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    size_t payload_length = 48 + (manifest->message_hash_count * 8);
    uint8_t payload[DRIP_MANIFEST_MAX_SIZE];
    size_t offset = 0;

    /* Build the payload to be signed. */
    /* vnb || vna || previous || null | link || messages || det */
    memcpy(payload + offset, &manifest->vnb, sizeof(manifest->vnb));
    offset += sizeof(manifest->vnb);

    memcpy(payload + offset, &manifest->vna, sizeof(manifest->vna));
    offset += sizeof(manifest->vna);

    memcpy(payload + offset, manifest->previous_manifest_hash, sizeof(manifest->previous_manifest_hash));
    offset += sizeof(manifest->previous_manifest_hash);

    /* Current manifest hash should be null filled when signing. */
    memset(payload + offset, 0, sizeof(manifest->current_manifest_hash));
    offset += sizeof(manifest->current_manifest_hash);

    memcpy(payload + offset, manifest->drip_link_hash, sizeof(manifest->drip_link_hash));
    offset += sizeof(manifest->drip_link_hash);

    /* Copy each filled hash to the payload. In other words remove the empty */
    /* hash slots from the payload. */
    for (uint8_t i = 0; i < manifest->message_hash_count; i++) {
        memcpy(payload + offset, manifest->evidence[i], sizeof(drip_hash_t));
        offset += sizeof(drip_hash_t);
    }

    memcpy(payload + offset, manifest->det, sizeof(manifest->det));
    offset += sizeof(manifest->det);

    size_t signature_length = 0;
    int rc = callback(context, payload, payload_length, manifest->signature, DRIP_SIGNATURE_SIZE, &signature_length);
    if (rc != 0) {
        return DRIP_ERROR_CALLBACK_FAILED;
    }

    return DRIP_SUCCESS;
}

int drip_manifest_verify(
    drip_manifest_t *manifest,
    rid_manifest_verify_cb_t callback,
    void *context
) {
    if (manifest == NULL || callback == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    size_t payload_length = 48 + (manifest->message_hash_count * 8);
    uint8_t payload[DRIP_MANIFEST_MAX_SIZE];
    size_t offset = 0;

    memcpy(payload + offset, &manifest->vnb, sizeof(manifest->vnb));
    offset += sizeof(manifest->vnb);

    memcpy(payload + offset, &manifest->vna, sizeof(manifest->vna));
    offset += sizeof(manifest->vna);

    memcpy(payload + offset, manifest->previous_manifest_hash, sizeof(manifest->previous_manifest_hash));
    offset += sizeof(manifest->previous_manifest_hash);

    memset(payload + offset, 0, sizeof(manifest->current_manifest_hash));
    offset += sizeof(manifest->current_manifest_hash);

    memcpy(payload + offset, manifest->drip_link_hash, sizeof(manifest->drip_link_hash));
    offset += sizeof(manifest->drip_link_hash);

    for (uint8_t i = 0; i < manifest->message_hash_count; i++) {
        memcpy(payload + offset, manifest->evidence[i], sizeof(drip_hash_t));
        offset += sizeof(drip_hash_t);
    }

    memcpy(payload + offset, manifest->det, sizeof(manifest->det));

    int rc = callback(context, payload, payload_length, manifest->signature, DRIP_SIGNATURE_SIZE);
    if (rc != 0) {
        return DRIP_ERROR_CALLBACK_FAILED;
    }

    return DRIP_SUCCESS;
}

int drip_manifest_encode(
    const drip_manifest_t *manifest,
    uint8_t *buffer,
    size_t buffer_size,
    size_t *encoded_length
) {
    if (manifest == NULL || buffer == NULL || encoded_length == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    size_t required_length = DRIP_MANIFEST_MIN_SIZE +
        manifest->message_hash_count * DRIP_HASH_SIZE;

    if (buffer_size < required_length) {
        return DRIP_ERROR_BUFFER_TOO_SMALL;
    }

    size_t offset = 0;

    memcpy(buffer + offset, &manifest->sam_type, DRIP_SAM_TYPE_SIZE);
    offset += DRIP_SAM_TYPE_SIZE;

    memcpy(buffer + offset, &manifest->vnb, DRIP_TIMESTAMP_SIZE);
    offset += DRIP_TIMESTAMP_SIZE;

    memcpy(buffer + offset, &manifest->vna, DRIP_TIMESTAMP_SIZE);
    offset += DRIP_TIMESTAMP_SIZE;

    memcpy(buffer + offset, manifest->previous_manifest_hash, DRIP_HASH_SIZE);
    offset += DRIP_HASH_SIZE;

    memcpy(buffer + offset, manifest->current_manifest_hash, DRIP_HASH_SIZE);
    offset += DRIP_HASH_SIZE;

    memcpy(buffer + offset, manifest->drip_link_hash, DRIP_HASH_SIZE);
    offset += DRIP_HASH_SIZE;

    for (uint8_t i = 0; i < manifest->message_hash_count; i++) {
        memcpy(buffer + offset, manifest->evidence[i], DRIP_HASH_SIZE);
        offset += DRIP_HASH_SIZE;
    }

    memcpy(buffer + offset, manifest->det, DRIP_DET_SIZE);
    offset += DRIP_DET_SIZE;

    memcpy(buffer + offset, manifest->signature, DRIP_SIGNATURE_SIZE);
    offset += DRIP_SIGNATURE_SIZE;

    *encoded_length = offset;

    return DRIP_SUCCESS;
}

int drip_manifest_decode(
    drip_manifest_t *manifest,
    const uint8_t *buffer,
    size_t buffer_size
) {
    if (manifest == NULL || buffer == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    if (buffer_size < DRIP_MANIFEST_MIN_SIZE) {
        return DRIP_ERROR_BUFFER_TOO_SMALL;
    }

    size_t evidence_size = buffer_size - DRIP_MANIFEST_MIN_SIZE;
    if (evidence_size % DRIP_HASH_SIZE != 0) {
        return DRIP_ERROR_INVALID_LENGTH;
    }

    uint8_t message_hash_count = (uint8_t)(evidence_size / DRIP_HASH_SIZE);
    if (message_hash_count > DRIP_MANIFEST_MESSAGES_MAX) {
        return DRIP_ERROR_ARRAY_FULL;
    }

    drip_manifest_init(manifest);

    size_t offset = 0;

    memcpy(&manifest->sam_type, buffer + offset, DRIP_SAM_TYPE_SIZE);
    offset += DRIP_SAM_TYPE_SIZE;

    memcpy(&manifest->vnb, buffer + offset, DRIP_TIMESTAMP_SIZE);
    offset += DRIP_TIMESTAMP_SIZE;

    memcpy(&manifest->vna, buffer + offset, DRIP_TIMESTAMP_SIZE);
    offset += DRIP_TIMESTAMP_SIZE;

    memcpy(manifest->previous_manifest_hash, buffer + offset, DRIP_HASH_SIZE);
    offset += DRIP_HASH_SIZE;

    memcpy(manifest->current_manifest_hash, buffer + offset, DRIP_HASH_SIZE);
    offset += DRIP_HASH_SIZE;

    memcpy(manifest->drip_link_hash, buffer + offset, DRIP_HASH_SIZE);
    offset += DRIP_HASH_SIZE;

    for (uint8_t i = 0; i < message_hash_count; i++) {
        memcpy(manifest->evidence[i], buffer + offset, DRIP_HASH_SIZE);
        offset += DRIP_HASH_SIZE;
    }
    manifest->message_hash_count = message_hash_count;

    memcpy(manifest->det, buffer + offset, DRIP_DET_SIZE);
    offset += DRIP_DET_SIZE;

    memcpy(manifest->signature, buffer + offset, DRIP_SIGNATURE_SIZE);
    offset += DRIP_SIGNATURE_SIZE;

    return DRIP_SUCCESS;
}
