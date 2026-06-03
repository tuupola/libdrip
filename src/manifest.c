#include <stdio.h>
#include <string.h>

#include "drip/hash.h"
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

    manifest->vnb = unixtime - DRIP_TIMESTAMP_EPOCH;

    return DRIP_SUCCESS;
}

uint32_t drip_manifest_get_vnb_unixtime(const drip_manifest_t *manifest) {
    if (NULL == manifest) {
        return 0;
    }

    return manifest->vnb + DRIP_TIMESTAMP_EPOCH;
}

int drip_manifest_set_vna_unixtime(drip_manifest_t *manifest, uint32_t unixtime) {
    if (manifest == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    manifest->vna = unixtime - DRIP_TIMESTAMP_EPOCH;
    return DRIP_SUCCESS;
}

uint32_t drip_manifest_get_vna_unixtime(const drip_manifest_t *manifest) {
    if (manifest == NULL) {
        return 0;
    }
    return manifest->vna + DRIP_TIMESTAMP_EPOCH;
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

const drip_hash_t *drip_manifest_get_previous_hash(const drip_manifest_t *manifest) {
    if (manifest == NULL) {
        return NULL;
    }
    return &manifest->previous_hash;
}

int drip_manifest_set_previous_hash(drip_manifest_t *manifest, const drip_hash_t *hash) {
    if (manifest == NULL || hash == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    memcpy(manifest->previous_hash, hash, sizeof(drip_hash_t));
    return DRIP_SUCCESS;
}

const drip_hash_t *drip_manifest_get_current_hash(const drip_manifest_t *manifest) {
    if (manifest == NULL) {
        return NULL;
    }
    return &manifest->current_hash;
}

int drip_manifest_set_current_hash(drip_manifest_t *manifest, const drip_hash_t *hash) {
    if (manifest == NULL || hash == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    memcpy(manifest->current_hash, hash, sizeof(drip_hash_t));
    return DRIP_SUCCESS;
}

int drip_manifest_update_current_hash(
    drip_manifest_t *manifest,
    drip_hash_cb_t callback,
    void *context
) {
    if (manifest == NULL || callback == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    uint8_t buffer[DRIP_HASH_SIZE * (2 + DRIP_MANIFEST_EVIDENCE_MAX)];
    size_t offset = 0;

    memcpy(buffer + offset, manifest->previous_hash, DRIP_HASH_SIZE);
    offset += DRIP_HASH_SIZE;

    /* Current hash is zeroed. */
    memset(buffer + offset, 0, DRIP_HASH_SIZE);
    offset += DRIP_HASH_SIZE;

    for (uint8_t i = 0; i < manifest->evidence_count; i++) {
        memcpy(buffer + offset, manifest->evidence[i], DRIP_HASH_SIZE);
        offset += DRIP_HASH_SIZE;
    }

    size_t hash_length = 0;
    int rc = callback(
        context, buffer, offset, manifest->current_hash, DRIP_HASH_SIZE, &hash_length
    );
    if (rc != 0) {
        return DRIP_ERROR_CALLBACK_FAILED;
    }

    return DRIP_SUCCESS;
}

const drip_hash_t *drip_manifest_get_link_hash(const drip_manifest_t *manifest) {
    if (manifest == NULL) {
        return NULL;
    }
    return &manifest->link_hash;
}

int drip_manifest_set_link_hash(drip_manifest_t *manifest, const drip_hash_t *hash) {
    if (manifest == NULL || hash == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    memcpy(manifest->link_hash, hash, sizeof(drip_hash_t));
    return DRIP_SUCCESS;
}

const drip_det_t *drip_manifest_get_det(const drip_manifest_t *manifest) {
    if (manifest == NULL) {
        return NULL;
    }
    return &manifest->det;
}

int drip_manifest_set_det(drip_manifest_t *manifest, const drip_det_t *det) {
    if (manifest == NULL || det == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    memcpy(manifest->det, det, sizeof(drip_det_t));
    return DRIP_SUCCESS;
}

const drip_signature_t *drip_manifest_get_signature(const drip_manifest_t *manifest) {
    if (manifest == NULL) {
        return NULL;
    }
    return &manifest->signature;
}

int drip_manifest_set_signature(drip_manifest_t *manifest, const drip_signature_t *signature) {
    if (manifest == NULL || signature == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    memcpy(manifest->signature, signature, sizeof(drip_signature_t));
    return DRIP_SUCCESS;
}

int drip_manifest_add_evidence(drip_manifest_t *manifest, const drip_hash_t *hash) {
    if (manifest == NULL || hash == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    if (manifest->evidence_count >= DRIP_MANIFEST_EVIDENCE_MAX) {
        return DRIP_ERROR_ARRAY_FULL;
    }
    memcpy(manifest->evidence[manifest->evidence_count], hash, sizeof(drip_hash_t));
    manifest->evidence_count++;
    return DRIP_SUCCESS;
}

const drip_hash_t *drip_manifest_get_evidence_at(const drip_manifest_t *manifest, uint8_t index) {
    if (manifest == NULL) {
        return NULL;
    }
    if (index >= manifest->evidence_count) {
        return NULL;
    }
    return &manifest->evidence[index];
}

int drip_manifest_sign(
    drip_manifest_t *manifest,
    drid_manifest_sign_cb_t callback,
    void *context
) {
    if (manifest == NULL || callback == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    size_t payload_length = 48 + (manifest->evidence_count * 8);
    uint8_t payload[DRIP_MANIFEST_MAX_SIZE];
    size_t offset = 0;

    /* Build the payload to be signed. */
    /* vnb || vna || previous || current | link || messages || det */
    memcpy(payload + offset, &manifest->vnb, sizeof(manifest->vnb));
    offset += sizeof(manifest->vnb);

    memcpy(payload + offset, &manifest->vna, sizeof(manifest->vna));
    offset += sizeof(manifest->vna);

    memcpy(payload + offset, manifest->previous_hash, sizeof(manifest->previous_hash));
    offset += sizeof(manifest->previous_hash);

    memcpy(payload + offset, &manifest->current_hash, sizeof(manifest->current_hash));
    offset += sizeof(manifest->current_hash);

    memcpy(payload + offset, manifest->link_hash, sizeof(manifest->link_hash));
    offset += sizeof(manifest->link_hash);

    /* Copy each filled hash to the payload. In other words remove the empty */
    /* hash slots from the payload. */
    for (uint8_t i = 0; i < manifest->evidence_count; i++) {
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
    drip_manifest_verify_cb_t callback,
    void *context
) {
    if (manifest == NULL || callback == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    size_t payload_length = 48 + (manifest->evidence_count * 8);
    uint8_t payload[DRIP_MANIFEST_MAX_SIZE];
    size_t offset = 0;

    memcpy(payload + offset, &manifest->vnb, sizeof(manifest->vnb));
    offset += sizeof(manifest->vnb);

    memcpy(payload + offset, &manifest->vna, sizeof(manifest->vna));
    offset += sizeof(manifest->vna);

    memcpy(payload + offset, manifest->previous_hash, sizeof(manifest->previous_hash));
    offset += sizeof(manifest->previous_hash);

    memcpy(payload + offset, &manifest->current_hash, sizeof(manifest->current_hash));
    offset += sizeof(manifest->current_hash);

    memcpy(payload + offset, manifest->link_hash, sizeof(manifest->link_hash));
    offset += sizeof(manifest->link_hash);

    for (uint8_t i = 0; i < manifest->evidence_count; i++) {
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
        manifest->evidence_count * DRIP_HASH_SIZE;

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

    memcpy(buffer + offset, manifest->previous_hash, DRIP_HASH_SIZE);
    offset += DRIP_HASH_SIZE;

    memcpy(buffer + offset, manifest->current_hash, DRIP_HASH_SIZE);
    offset += DRIP_HASH_SIZE;

    memcpy(buffer + offset, manifest->link_hash, DRIP_HASH_SIZE);
    offset += DRIP_HASH_SIZE;

    for (uint8_t i = 0; i < manifest->evidence_count; i++) {
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

    uint8_t evidence_count = (uint8_t)(evidence_size / DRIP_HASH_SIZE);
    if (evidence_count > DRIP_MANIFEST_EVIDENCE_MAX) {
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

    memcpy(manifest->previous_hash, buffer + offset, DRIP_HASH_SIZE);
    offset += DRIP_HASH_SIZE;

    memcpy(manifest->current_hash, buffer + offset, DRIP_HASH_SIZE);
    offset += DRIP_HASH_SIZE;

    memcpy(manifest->link_hash, buffer + offset, DRIP_HASH_SIZE);
    offset += DRIP_HASH_SIZE;

    for (uint8_t i = 0; i < evidence_count; i++) {
        memcpy(manifest->evidence[i], buffer + offset, DRIP_HASH_SIZE);
        offset += DRIP_HASH_SIZE;
    }
    manifest->evidence_count = evidence_count;

    memcpy(manifest->det, buffer + offset, DRIP_DET_SIZE);
    offset += DRIP_DET_SIZE;

    memcpy(manifest->signature, buffer + offset, DRIP_SIGNATURE_SIZE);
    offset += DRIP_SIGNATURE_SIZE;

    return DRIP_SUCCESS;
}

int drip_manifest_to_json(const drip_manifest_t *manifest, char *buffer, size_t buffer_size) {
    if (manifest == NULL || buffer == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    const drip_hash_t *previous_hash = drip_manifest_get_previous_hash(manifest);
    const drip_hash_t *current_hash = drip_manifest_get_current_hash(manifest);
    const drip_hash_t *link_hash = drip_manifest_get_link_hash(manifest);

    const drip_det_t *det = drip_manifest_get_det(manifest);

    char det_hex[33];
    for (uint8_t i = 0; i < 16; i++) {
        snprintf(det_hex + i * 2, 3, "%02x", (*det)[i]);
    }

    const drip_signature_t *signature = drip_manifest_get_signature(manifest);

    char previous_hex[17], current_hex[17], link_hex[17];
    drip_hash_to_hex(previous_hash, previous_hex, sizeof(previous_hex));
    drip_hash_to_hex(current_hash, current_hex, sizeof(current_hex));
    drip_hash_to_hex(link_hash, link_hex, sizeof(link_hex));

    char sig_hex[129];
    size_t sig_pos = 0;
    for (uint8_t i = 0; i < 64; i++) {
        sig_pos += snprintf(sig_hex + sig_pos, 3, "%02x", (*signature)[i]);
    }

    char evidence_json[256] = "[";
    for (uint8_t i = 0; i < manifest->evidence_count; i++) {
        if (i > 0) {
            strcat(evidence_json, ",");
        }
        char ev_hex[17];
        drip_hash_to_hex(&manifest->evidence[i], ev_hex, sizeof(ev_hex));
        strcat(evidence_json, "\"");
        strcat(evidence_json, ev_hex);
        strcat(evidence_json, "\"");
    }
    strcat(evidence_json, "]");

    return snprintf(
        buffer,
        buffer_size,
        "{"
        "\"sam_type\": %u, "
        "\"vnb\": %u, "
        "\"vna\": %u, "
        "\"previous_hash\": \"%s\", "
        "\"current_hash\": \"%s\", "
        "\"link_hash\": \"%s\", "
        "\"evidence_count\": %u, "
        "\"evidence\": %s, "
        "\"det\": \"%s\", "
        "\"signature\": \"%s\""
        "}",
        manifest->sam_type,
        manifest->vnb,
        manifest->vna,
        previous_hex,
        current_hex,
        link_hex,
        manifest->evidence_count,
        evidence_json,
        det_hex,
        sig_hex
    );
}
