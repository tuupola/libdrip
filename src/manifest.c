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
