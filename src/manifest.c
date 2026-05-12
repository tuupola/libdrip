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
