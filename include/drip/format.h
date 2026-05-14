#ifndef DRIP_FORMAT_H
#define DRIP_FORMAT_H

#include <stddef.h>
#include <stdint.h>

typedef enum {
    DRIP_SUCCESS = 0,
    DRIP_ERROR_NULL_POINTER = -1,
    DRIP_ERROR_BUFFER_TOO_SMALL = -2,
    DRIP_ERROR_ARRAY_FULL = -3,
    DRIP_ERROR_INVALID_INDEX = -4,
    DRIP_ERROR_CALLBACK_FAILED = -5,
} drip_status_t;

typedef enum {
    DRIP_SAM_TYPE_LINK = 0x01,
    DRIP_SAM_TYPE_WRAPPER = 0x02,
    DRIP_SAM_TYPE_MANIFEST = 0x03,
    DRIP_SAM_TYPE_FRAME = 0x04,
} drip_sam_type_t;

#endif
