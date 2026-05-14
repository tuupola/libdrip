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
    if (manifest->message_hash_count >= DRIP_MANIFEST_MESSAGE_MAX) {
        return DRIP_ERROR_ARRAY_FULL;
    }
    memcpy(manifest->message_hash_array[manifest->message_hash_count], hash, sizeof(drip_hash_t));
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
    memcpy(hash, manifest->message_hash_array[index], sizeof(drip_hash_t));
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
    uint8_t payload[DRIP_AUTH_DATA_MAX];
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
        memcpy(payload + offset, manifest->message_hash_array[i], sizeof(drip_hash_t));
        offset += sizeof(drip_hash_t);
    }

    memcpy(payload + offset, manifest->det, sizeof(manifest->det));
    offset += sizeof(manifest->det);

    size_t signature_length = 0;
    int rc = callback(context, payload, payload_length, manifest->signature, DRIP_SIGNATURE_LEN, &signature_length);
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
    uint8_t payload[DRIP_AUTH_DATA_MAX];
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
        memcpy(payload + offset, manifest->message_hash_array[i], sizeof(drip_hash_t));
        offset += sizeof(drip_hash_t);
    }

    memcpy(payload + offset, manifest->det, sizeof(manifest->det));

    int rc = callback(context, payload, payload_length, manifest->signature, DRIP_SIGNATURE_LEN);
    if (rc != 0) {
        return DRIP_ERROR_VERIFICATION_FAILED;
    }

    return DRIP_SUCCESS;
}
