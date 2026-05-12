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
