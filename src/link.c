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

int drip_link_decode(drip_link_t *link, const uint8_t *buffer, size_t buffer_size) {
    if (link == NULL || buffer == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    if (buffer_size < DRIP_LINK_SIZE) {
        return DRIP_ERROR_BUFFER_TOO_SMALL;
    }

    if (buffer_size > DRIP_LINK_SIZE) {
        return DRIP_ERROR_BUFFER_TOO_LARGE;
    }

    memcpy(link, buffer, DRIP_LINK_SIZE);

    if (link->sam_type != DRIP_SAM_TYPE_LINK) {
        return DRIP_ERROR_INVALID_SAM_TYPE;
    }

    return DRIP_SUCCESS;
}

int drip_link_encode(
    const drip_link_t *link,
    uint8_t *buffer,
    size_t buffer_size,
    size_t *encoded_length
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

int drip_link_sign(
    drip_link_t *link,
    drip_link_sign_cb_t callback,
    void *context
) {
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

    size_t signature_length = 0;
    int rc = callback(context, payload, payload_length, link->signature, DRIP_SIGNATURE_SIZE, &signature_length);
    if (rc != 0) {
        return DRIP_ERROR_CALLBACK_FAILED;
    }
    if (signature_length != DRIP_SIGNATURE_SIZE) {
        return DRIP_ERROR_INVALID_LENGTH;
    }

    return DRIP_SUCCESS;
}

int drip_link_verify(
    drip_link_t *link,
    drip_link_verify_cb_t callback,
    void *context
) {
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

    int rc = callback(context, payload, payload_length, link->signature, DRIP_SIGNATURE_SIZE);
    if (rc != 0) {
        return DRIP_ERROR_CALLBACK_FAILED;
    }

    return DRIP_SUCCESS;
}

int drip_link_to_json(
    const drip_link_t *link,
    char *buffer,
    size_t buffer_size
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

    return snprintf(
        buffer,
        buffer_size,
        "{"
        "\"sam_type\": %u, "
        "\"vnb\": %u, "
        "\"vna\": %u, "
        "\"child_det\": \"%s\", "
        "\"child_hi\": \"%s\", "
        "\"parent_det\": \"%s\", "
        "\"signature\": \"%s\""
        "}",
        link->sam_type,
        link->vnb,
        link->vna,
        child_det_hex,
        child_hi_hex,
        parent_det_hex,
        sig_hex
    );
}
