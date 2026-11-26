#include "drip/format.h"
#include "drip/link.h"
#include "drip/manifest.h"
#include "drip/wrapper.h"

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
