#ifndef DRIP_UNION_H
#define DRIP_UNION_H

#include "drip/link.h"
#include "drip/manifest.h"
#include "drip/wrapper.h"

/**
 * @brief Storage large enough for any decoded DRIP SAM format.
 */
typedef union drip_format {
    drip_link_t link;
    drip_wrapper_t wrapper;
    drip_manifest_t manifest;
} drip_format_t;

#endif /* DRIP_UNION_H */
