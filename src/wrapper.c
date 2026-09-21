#include <stdio.h>
#include <string.h>

#include "drip/wrapper.h"

int drip_wrapper_init(drip_wrapper_t *wrapper) {
    if (wrapper == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    memset(wrapper, 0, sizeof(drip_wrapper_t));
    wrapper->sam_type = DRIP_SAM_TYPE_WRAPPER;

    return DRIP_SUCCESS;
}

uint32_t drip_wrapper_get_vnb(const drip_wrapper_t *wrapper) {
    if (wrapper == NULL) {
        return 0;
    }
    return wrapper->vnb;
}

int drip_wrapper_set_vnb(drip_wrapper_t *wrapper, uint32_t vnb) {
    if (wrapper == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    if (vnb > (UINT32_MAX - DRIP_TIMESTAMP_EPOCH)) {
        return DRIP_ERROR_OUT_OF_RANGE;
    }
    wrapper->vnb = vnb;
    return DRIP_SUCCESS;
}

int drip_wrapper_set_vnb_unixtime(drip_wrapper_t *wrapper, uint32_t unixtime) {
    if (wrapper == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    if (unixtime < DRIP_TIMESTAMP_EPOCH) {
        return DRIP_ERROR_OUT_OF_RANGE;
    }

    wrapper->vnb = unixtime - DRIP_TIMESTAMP_EPOCH;

    return DRIP_SUCCESS;
}

uint32_t drip_wrapper_get_vnb_unixtime(const drip_wrapper_t *wrapper) {
    if (wrapper == NULL) {
        return 0;
    }

    return wrapper->vnb + DRIP_TIMESTAMP_EPOCH;
}

int drip_wrapper_set_vna_unixtime(drip_wrapper_t *wrapper, uint32_t unixtime) {
    if (wrapper == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    if (unixtime < DRIP_TIMESTAMP_EPOCH) {
        return DRIP_ERROR_OUT_OF_RANGE;
    }
    wrapper->vna = unixtime - DRIP_TIMESTAMP_EPOCH;
    return DRIP_SUCCESS;
}

uint32_t drip_wrapper_get_vna_unixtime(const drip_wrapper_t *wrapper) {
    if (wrapper == NULL) {
        return 0;
    }
    return wrapper->vna + DRIP_TIMESTAMP_EPOCH;
}

uint32_t drip_wrapper_get_vna(const drip_wrapper_t *wrapper) {
    if (wrapper == NULL) {
        return 0;
    }
    return wrapper->vna;
}

int drip_wrapper_set_vna(drip_wrapper_t *wrapper, uint32_t vna) {
    if (wrapper == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    if (vna > (UINT32_MAX - DRIP_TIMESTAMP_EPOCH)) {
        return DRIP_ERROR_OUT_OF_RANGE;
    }
    wrapper->vna = vna;
    return DRIP_SUCCESS;
}

const drip_det_t *drip_wrapper_get_det(const drip_wrapper_t *wrapper) {
    if (wrapper == NULL) {
        return NULL;
    }
    return &wrapper->det;
}

int drip_wrapper_set_det(drip_wrapper_t *wrapper, const drip_det_t *det) {
    if (wrapper == NULL || det == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    memcpy(wrapper->det, det, sizeof(drip_det_t));
    return DRIP_SUCCESS;
}

const drip_signature_t *drip_wrapper_get_signature(const drip_wrapper_t *wrapper) {
    if (wrapper == NULL) {
        return NULL;
    }
    return &wrapper->signature;
}

int drip_wrapper_set_signature(
    drip_wrapper_t *wrapper, const drip_signature_t *signature
) {
    if (wrapper == NULL || signature == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    memcpy(wrapper->signature, signature, sizeof(drip_signature_t));
    return DRIP_SUCCESS;
}

int drip_wrapper_validate(const drip_wrapper_t *wrapper) {
    if (wrapper == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    if (wrapper->sam_type != DRIP_SAM_TYPE_WRAPPER) {
        return DRIP_ERROR_INVALID_SAM_TYPE;
    }
    if (wrapper->vnb > wrapper->vna) {
        return DRIP_ERROR_INVALID_TIMESTAMP;
    }
    if (wrapper->evidence_count > DRIP_WRAPPER_EVIDENCE_MAX) {
        return DRIP_ERROR_ARRAY_OVERFLOW;
    }
    if (drip_det_validate(&wrapper->det) != DRIP_SUCCESS) {
        return DRIP_ERROR_INVALID_DET;
    }
    return DRIP_SUCCESS;
}

int drip_wrapper_add_evidence(
    drip_wrapper_t *wrapper, const uint8_t *buffer, size_t buffer_size
) {
    if (wrapper == NULL || buffer == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    if (buffer_size != RID_MESSAGE_SIZE) {
        return DRIP_ERROR_INVALID_LENGTH;
    }
    if (wrapper->evidence_count >= DRIP_WRAPPER_EVIDENCE_MAX) {
        return DRIP_ERROR_ARRAY_OVERFLOW;
    }
    memcpy(wrapper->evidence[wrapper->evidence_count], buffer, RID_MESSAGE_SIZE);
    wrapper->evidence_count++;
    return DRIP_SUCCESS;
}

uint8_t drip_wrapper_evidence_count(const drip_wrapper_t *wrapper) {
    if (wrapper == NULL) {
        return 0;
    }
    return wrapper->evidence_count;
}

const uint8_t *
drip_wrapper_get_evidence_at(const drip_wrapper_t *wrapper, uint8_t index) {
    if (wrapper == NULL) {
        return NULL;
    }
    if (index >= wrapper->evidence_count) {
        return NULL;
    }
    return wrapper->evidence[index];
}

int drip_wrapper_sign(
    drip_wrapper_t *wrapper, drip_wrapper_sign_cb_t callback, void *context
) {
    if (wrapper == NULL || callback == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    size_t payload_length = (DRIP_TIMESTAMP_SIZE * 2) +
        (wrapper->evidence_count * RID_MESSAGE_SIZE) + DRIP_DET_SIZE;
    uint8_t payload[DRIP_WRAPPER_MAX_SIZE];
    size_t offset = 0;

    /* vnb || vna || evidence || det */
    memcpy(payload + offset, &wrapper->vnb, sizeof(wrapper->vnb));
    offset += sizeof(wrapper->vnb);

    memcpy(payload + offset, &wrapper->vna, sizeof(wrapper->vna));
    offset += sizeof(wrapper->vna);

    for (uint8_t i = 0; i < wrapper->evidence_count; i++) {
        memcpy(payload + offset, wrapper->evidence[i], RID_MESSAGE_SIZE);
        offset += RID_MESSAGE_SIZE;
    }

    memcpy(payload + offset, wrapper->det, sizeof(wrapper->det));
    offset += sizeof(wrapper->det);

    size_t output_length = 0;
    int rc = callback(
        context, payload, payload_length, wrapper->signature, DRIP_SIGNATURE_SIZE,
        &output_length
    );
    if (rc != 0) {
        return DRIP_ERROR_CALLBACK_FAILED;
    }

    return DRIP_SUCCESS;
}

int drip_wrapper_verify(
    drip_wrapper_t *wrapper, drip_wrapper_verify_cb_t callback, void *context
) {
    if (wrapper == NULL || callback == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    size_t payload_length = (DRIP_TIMESTAMP_SIZE * 2) +
        (wrapper->evidence_count * RID_MESSAGE_SIZE) + DRIP_DET_SIZE;
    uint8_t payload[DRIP_WRAPPER_MAX_SIZE];
    size_t offset = 0;

    memcpy(payload + offset, &wrapper->vnb, sizeof(wrapper->vnb));
    offset += sizeof(wrapper->vnb);

    memcpy(payload + offset, &wrapper->vna, sizeof(wrapper->vna));
    offset += sizeof(wrapper->vna);

    for (uint8_t i = 0; i < wrapper->evidence_count; i++) {
        memcpy(payload + offset, wrapper->evidence[i], RID_MESSAGE_SIZE);
        offset += RID_MESSAGE_SIZE;
    }

    memcpy(payload + offset, wrapper->det, sizeof(wrapper->det));

    int rc = callback(
        context, payload, payload_length, wrapper->signature, DRIP_SIGNATURE_SIZE
    );
    if (rc != 0) {
        return DRIP_ERROR_CALLBACK_FAILED;
    }

    return DRIP_SUCCESS;
}

int drip_wrapper_encode(
    const drip_wrapper_t *wrapper, uint8_t *buffer, size_t buffer_size,
    size_t *encoded_length
) {
    if (wrapper == NULL || buffer == NULL || encoded_length == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    size_t required_length =
        DRIP_WRAPPER_MIN_SIZE + wrapper->evidence_count * RID_MESSAGE_SIZE;

    if (buffer_size < required_length) {
        return DRIP_ERROR_BUFFER_TOO_SMALL;
    }

    size_t offset = 0;

    memcpy(buffer + offset, &wrapper->sam_type, DRIP_SAM_TYPE_SIZE);
    offset += DRIP_SAM_TYPE_SIZE;

    /* Add the timestamps. */
    memcpy(buffer + offset, &wrapper->vnb, DRIP_TIMESTAMP_SIZE);
    offset += DRIP_TIMESTAMP_SIZE;

    memcpy(buffer + offset, &wrapper->vna, DRIP_TIMESTAMP_SIZE);
    offset += DRIP_TIMESTAMP_SIZE;

    /* Add the evidence. */
    for (uint8_t i = 0; i < wrapper->evidence_count; i++) {
        memcpy(buffer + offset, wrapper->evidence[i], RID_MESSAGE_SIZE);
        offset += RID_MESSAGE_SIZE;
    }

    /* Add the det and signature. */
    memcpy(buffer + offset, wrapper->det, DRIP_DET_SIZE);
    offset += DRIP_DET_SIZE;

    memcpy(buffer + offset, wrapper->signature, DRIP_SIGNATURE_SIZE);
    offset += DRIP_SIGNATURE_SIZE;

    *encoded_length = offset;

    return DRIP_SUCCESS;
}

int drip_wrapper_decode(
    drip_wrapper_t *wrapper, const uint8_t *buffer, size_t buffer_size
) {
    if (wrapper == NULL || buffer == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    /* Not enough data for wrapper with 0 bytes of evidence. */
    if (buffer_size < DRIP_WRAPPER_MIN_SIZE) {
        return DRIP_ERROR_BUFFER_TOO_SMALL;
    }

    /* Evidence must be multiples of 25 bytes. */
    size_t evidence_size = buffer_size - DRIP_WRAPPER_MIN_SIZE;
    if (evidence_size % RID_MESSAGE_SIZE != 0) {
        return DRIP_ERROR_INVALID_LENGTH;
    }

    /* There can be maximum 4 evidence. */
    uint8_t evidence_count = (uint8_t)(evidence_size / RID_MESSAGE_SIZE);
    if (evidence_count > DRIP_WRAPPER_EVIDENCE_MAX) {
        return DRIP_ERROR_ARRAY_OVERFLOW;
    }

    drip_wrapper_init(wrapper);

    size_t offset = 0;

    memcpy(&wrapper->sam_type, buffer + offset, DRIP_SAM_TYPE_SIZE);
    offset += DRIP_SAM_TYPE_SIZE;

    if (wrapper->sam_type != DRIP_SAM_TYPE_WRAPPER) {
        return DRIP_ERROR_INVALID_SAM_TYPE;
    }

    /* Add the timestamps. */
    memcpy(&wrapper->vnb, buffer + offset, DRIP_TIMESTAMP_SIZE);
    offset += DRIP_TIMESTAMP_SIZE;

    memcpy(&wrapper->vna, buffer + offset, DRIP_TIMESTAMP_SIZE);
    offset += DRIP_TIMESTAMP_SIZE;

    /* Add the evidence. */
    for (uint8_t i = 0; i < evidence_count; i++) {
        memcpy(wrapper->evidence[i], buffer + offset, RID_MESSAGE_SIZE);
        offset += RID_MESSAGE_SIZE;
    }
    wrapper->evidence_count = evidence_count;

    /* Add the det and signature. */
    memcpy(wrapper->det, buffer + offset, DRIP_DET_SIZE);
    offset += DRIP_DET_SIZE;

    memcpy(wrapper->signature, buffer + offset, DRIP_SIGNATURE_SIZE);
    offset += DRIP_SIGNATURE_SIZE;

    return DRIP_SUCCESS;
}

int drip_wrapper_to_json(
    const drip_wrapper_t *wrapper, char *buffer, size_t buffer_size, size_t *json_length
) {
    if (wrapper == NULL || buffer == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    /* TODO */

    return DRIP_SUCCESS;
}
