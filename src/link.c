#include <stdio.h>
#include <string.h>

#include "drip/link.h"

#define SIGNED_PAYLOAD_SIZE 72

int drip_link_init(drip_link_t *link) {
    if (link == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    memset(link, 0, sizeof(drip_link_t));
    link->sam_type = DRIP_SAM_TYPE_LINK;

    return DRIP_SUCCESS;
}

uint32_t drip_link_get_vnb(const drip_link_t *link) {
    if (link == NULL) {
        return 0;
    }
    return link->vnb;
}

int drip_link_set_vnb(drip_link_t *link, uint32_t vnb) {
    if (link == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    if (vnb > (UINT32_MAX - DRIP_TIMESTAMP_EPOCH)) {
        return DRIP_ERROR_OUT_OF_RANGE;
    }
    link->vnb = vnb;
    return DRIP_SUCCESS;
}

uint32_t drip_link_get_vna(const drip_link_t *link) {
    if (link == NULL) {
        return 0;
    }
    return link->vna;
}

int drip_link_set_vna(drip_link_t *link, uint32_t vna) {
    if (link == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    if (vna > (UINT32_MAX - DRIP_TIMESTAMP_EPOCH)) {
        return DRIP_ERROR_OUT_OF_RANGE;
    }
    link->vna = vna;
    return DRIP_SUCCESS;
}

int drip_link_set_vnb_unixtime(drip_link_t *link, uint32_t unixtime) {
    if (link == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    if (unixtime < DRIP_TIMESTAMP_EPOCH) {
        return DRIP_ERROR_OUT_OF_RANGE;
    }

    link->vnb = unixtime - DRIP_TIMESTAMP_EPOCH;

    return DRIP_SUCCESS;
}

uint32_t drip_link_get_vnb_unixtime(const drip_link_t *link) {
    if (link == NULL) {
        return 0;
    }

    return link->vnb + DRIP_TIMESTAMP_EPOCH;
}

int drip_link_set_vna_unixtime(drip_link_t *link, uint32_t unixtime) {
    if (link == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    if (unixtime < DRIP_TIMESTAMP_EPOCH) {
        return DRIP_ERROR_OUT_OF_RANGE;
    }
    link->vna = unixtime - DRIP_TIMESTAMP_EPOCH;
    return DRIP_SUCCESS;
}

uint32_t drip_link_get_vna_unixtime(const drip_link_t *link) {
    if (link == NULL) {
        return 0;
    }
    return link->vna + DRIP_TIMESTAMP_EPOCH;
}

const drip_det_t *drip_link_get_child_det(const drip_link_t *link) {
    if (link == NULL) {
        return NULL;
    }
    return &link->child_det;
}

int drip_link_set_child_det(drip_link_t *link, const drip_det_t *det) {
    if (link == NULL || det == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    memcpy(link->child_det, det, sizeof(drip_det_t));
    return DRIP_SUCCESS;
}

const drip_hi_t *drip_link_get_child_hi(const drip_link_t *link) {
    if (link == NULL) {
        return NULL;
    }
    return &link->child_hi;
}

int drip_link_set_child_hi(drip_link_t *link, const drip_hi_t *hi) {
    if (link == NULL || hi == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    memcpy(link->child_hi, hi, sizeof(drip_hi_t));
    return DRIP_SUCCESS;
}

const drip_det_t *drip_link_get_parent_det(const drip_link_t *link) {
    if (link == NULL) {
        return NULL;
    }
    return &link->parent_det;
}

int drip_link_set_parent_det(drip_link_t *link, const drip_det_t *det) {
    if (link == NULL || det == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    memcpy(link->parent_det, det, sizeof(drip_det_t));
    return DRIP_SUCCESS;
}

const drip_signature_t *drip_link_get_signature(const drip_link_t *link) {
    if (link == NULL) {
        return NULL;
    }
    return &link->signature;
}

int drip_link_set_signature(drip_link_t *link, const drip_signature_t *signature) {
    if (link == NULL || signature == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    memcpy(link->signature, signature, sizeof(drip_signature_t));
    return DRIP_SUCCESS;
}

int drip_link_validate(const drip_link_t *link) {
    if (link == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    if (link->sam_type != DRIP_SAM_TYPE_LINK) {
        return DRIP_ERROR_INVALID_SAM_TYPE;
    }
    if (link->vnb > link->vna) {
        return DRIP_ERROR_INVALID_TIMESTAMP;
    }
    if (drip_det_validate(&link->child_det) != DRIP_SUCCESS) {
        return DRIP_ERROR_INVALID_CHILD_DET;
    }
    if (drip_det_validate(&link->parent_det) != DRIP_SUCCESS) {
        return DRIP_ERROR_INVALID_PARENT_DET;
    }
    return DRIP_SUCCESS;
}

int drip_link_decode(drip_link_t *link, const uint8_t *buffer, size_t buffer_size) {
    if (link == NULL || buffer == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    if (buffer_size < DRIP_LINK_SIZE) {
        return DRIP_ERROR_BUFFER_TOO_SMALL;
    }

    memcpy(link, buffer, DRIP_LINK_SIZE);

    if (link->sam_type != DRIP_SAM_TYPE_LINK) {
        return DRIP_ERROR_INVALID_SAM_TYPE;
    }

    return DRIP_SUCCESS;
}

int drip_link_encode(
    const drip_link_t *link, uint8_t *buffer, size_t buffer_size, size_t *encoded_length
) {
    if (link == NULL || buffer == NULL || encoded_length == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    if (buffer_size < DRIP_LINK_SIZE) {
        return DRIP_ERROR_BUFFER_TOO_SMALL;
    }

    memcpy(buffer, link, DRIP_LINK_SIZE);
    *encoded_length = DRIP_LINK_SIZE;

    return DRIP_SUCCESS;
}

int drip_link_sign(drip_link_t *link, drip_link_sign_cb_t callback, void *context) {
    if (link == NULL || callback == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    size_t payload_length = SIGNED_PAYLOAD_SIZE;
    uint8_t payload[SIGNED_PAYLOAD_SIZE];
    size_t offset = 0;

    memcpy(payload + offset, &link->vnb, sizeof(link->vnb));
    offset += sizeof(link->vnb);

    memcpy(payload + offset, &link->vna, sizeof(link->vna));
    offset += sizeof(link->vna);

    memcpy(payload + offset, link->child_det, sizeof(link->child_det));
    offset += sizeof(link->child_det);

    memcpy(payload + offset, link->child_hi, sizeof(link->child_hi));
    offset += sizeof(link->child_hi);

    memcpy(payload + offset, link->parent_det, sizeof(link->parent_det));
    offset += sizeof(link->parent_det);

    size_t output_length = 0;
    int rc = callback(
        context, payload, payload_length, link->signature, DRIP_SIGNATURE_SIZE,
        &output_length
    );
    if (rc != 0) {
        return DRIP_ERROR_CALLBACK_FAILED;
    }
    if (output_length != DRIP_SIGNATURE_SIZE) {
        return DRIP_ERROR_INVALID_LENGTH;
    }

    return DRIP_SUCCESS;
}

int drip_link_verify(
    const drip_link_t *link, uint32_t unixtime, drip_link_verify_cb_t callback,
    void *context
) {
    if (link == NULL || callback == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    if (unixtime != 0) {
        uint32_t vnb = drip_link_get_vnb_unixtime(link);
        uint32_t vna = drip_link_get_vna_unixtime(link);
        if (unixtime < vnb) {
            return DRIP_ERROR_TIMESTAMP_NOT_YET_VALID;
        }
        if (unixtime > vna) {
            return DRIP_ERROR_TIMESTAMP_EXPIRED;
        }
    }

    size_t payload_length = SIGNED_PAYLOAD_SIZE;
    uint8_t payload[SIGNED_PAYLOAD_SIZE];
    size_t offset = 0;

    memcpy(payload + offset, &link->vnb, sizeof(link->vnb));
    offset += sizeof(link->vnb);

    memcpy(payload + offset, &link->vna, sizeof(link->vna));
    offset += sizeof(link->vna);

    memcpy(payload + offset, link->child_det, sizeof(link->child_det));
    offset += sizeof(link->child_det);

    memcpy(payload + offset, link->child_hi, sizeof(link->child_hi));
    offset += sizeof(link->child_hi);

    memcpy(payload + offset, link->parent_det, sizeof(link->parent_det));
    offset += sizeof(link->parent_det);

    int rc =
        callback(context, payload, payload_length, link->signature, DRIP_SIGNATURE_SIZE);
    if (rc != 0) {
        return DRIP_ERROR_CALLBACK_FAILED;
    }

    return DRIP_SUCCESS;
}

int drip_link_verify_chain(
    const drip_link_t *link_array, size_t link_count, const drip_det_t *root_det,
    const drip_hi_t *root_hi, uint32_t unixtime, drip_hash_cb_t hash_cb,
    drip_link_verify_cb_t verify_cb
) {
    const drip_det_t *expected_det, *parent_det;
    const drip_hi_t *child_hi, *parent_hi;
    size_t i;
    int rc;

    if (link_array == NULL || root_det == NULL || root_hi == NULL || hash_cb == NULL ||
        verify_cb == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    if (link_count == 0) {
        return DRIP_ERROR_VERIFICATION_FAILED;
    }

    /* First expected det is the root, which is often the APEX. */
    expected_det = root_det;
    parent_hi = root_hi;

    for (i = 0; i < link_count; i++) {
        /* Make sure current link is structurally valid. */
        rc = drip_link_validate(&link_array[i]);
        if (rc != DRIP_SUCCESS) {
            return rc;
        }

        /* Make sure next link's parent is the previous links's child. */
        parent_det = drip_link_get_parent_det(&link_array[i]);
        if (memcmp(parent_det, expected_det, DRIP_DET_SIZE) != 0) {
            return DRIP_ERROR_VERIFICATION_FAILED;
        }
        expected_det = drip_link_get_child_det(&link_array[i]);

        /* Make sure child DET's hash matches its child HI. */
        child_hi = drip_link_get_child_hi(&link_array[i]);
        rc = drip_det_verify(expected_det, child_hi, hash_cb, NULL);
        if (rc != DRIP_SUCCESS) {
            return rc;
        }

        /* Make sure each Link is signed by the parent HI. */
        rc = drip_link_verify(&link_array[i], unixtime, verify_cb, (void *)parent_hi);
        if (rc != DRIP_SUCCESS) {
            return rc;
        }
        parent_hi = child_hi;
    }

    return DRIP_SUCCESS;
}

int drip_link_to_json(
    const drip_link_t *link, char *buffer, size_t buffer_size, size_t *json_length
) {
    if (link == NULL || buffer == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    const drip_det_t *child_det = drip_link_get_child_det(link);
    const drip_hi_t *child_hi = drip_link_get_child_hi(link);
    const drip_det_t *parent_det = drip_link_get_parent_det(link);
    const drip_signature_t *signature = drip_link_get_signature(link);

    char child_det_hex[33];
    char child_hi_hex[65];
    char parent_det_hex[33];
    for (uint8_t i = 0; i < 16; i++) {
        snprintf(child_det_hex + i * 2, 3, "%02x", (*child_det)[i]);
        snprintf(parent_det_hex + i * 2, 3, "%02x", (*parent_det)[i]);
    }
    for (uint8_t i = 0; i < 32; i++) {
        snprintf(child_hi_hex + i * 2, 3, "%02x", (*child_hi)[i]);
    }

    char sig_hex[129];
    size_t sig_pos = 0;
    for (uint8_t i = 0; i < 64; i++) {
        sig_pos += snprintf(sig_hex + sig_pos, 3, "%02x", (*signature)[i]);
    }

    int needed = snprintf(
        buffer, buffer_size,
        "{"
        "\"sam_type\": %u, "
        "\"vnb\": %u, "
        "\"vna\": %u, "
        "\"child_det\": \"%s\", "
        "\"child_hi\": \"%s\", "
        "\"parent_det\": \"%s\", "
        "\"signature\": \"%s\""
        "}",
        link->sam_type, link->vnb, link->vna, child_det_hex, child_hi_hex, parent_det_hex,
        sig_hex
    );

    if (json_length != NULL) {
        /* If snprintf() fails 0 bytes needed */
        *json_length = (needed < 0) ? 0 : (size_t)needed;
    }

    if ((size_t)needed >= buffer_size) {
        return DRIP_ERROR_BUFFER_TOO_SMALL;
    }

    return DRIP_SUCCESS;
}
