#include "drip/link.h"
#include "drip/manifest.h"
#include "drip/wrapper.h"

int drip_format_decode(void *format, const uint8_t *buffer, size_t buffer_size) {
    uint8_t sam_type;

    if (format == NULL || buffer == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    /* Make sure buffer[0] exists. */
    if (buffer_size < 1) {
        return DRIP_ERROR_BUFFER_TOO_SMALL;
    }

    /* SAM type is the first byte. */
    sam_type = buffer[0];

    switch (sam_type) {
        case DRIP_SAM_TYPE_LINK:
            return drip_link_decode(format, buffer, buffer_size);
        case DRIP_SAM_TYPE_WRAPPER:
            return drip_wrapper_decode(format, buffer, buffer_size);
        case DRIP_SAM_TYPE_MANIFEST:
            return drip_manifest_decode(format, buffer, buffer_size);
        default:
            return DRIP_ERROR_INVALID_SAM_TYPE;
    }
}

#ifndef DRIP_DISABLE_JSON
int drip_format_to_json(
    const void *format, char *buffer, size_t buffer_size, size_t *json_length
) {
    const uint8_t *sam_type;

    if (format == NULL || (buffer == NULL && json_length == NULL)) {
        return DRIP_ERROR_NULL_POINTER;
    }

    /* SAM type is the first byte. */
    sam_type = (const uint8_t *)format;

    switch (*sam_type) {
        case DRIP_SAM_TYPE_LINK:
            return drip_link_to_json(
                (const drip_link_t *)format, buffer, buffer_size, json_length
            );
        case DRIP_SAM_TYPE_WRAPPER:
            return drip_wrapper_to_json(
                (const drip_wrapper_t *)format, buffer, buffer_size, json_length
            );
        case DRIP_SAM_TYPE_MANIFEST:
            return drip_manifest_to_json(
                (const drip_manifest_t *)format, buffer, buffer_size, json_length
            );
        default:
            return DRIP_ERROR_INVALID_SAM_TYPE;
    }
}
#endif /* DRIP_DISABLE_JSON */
