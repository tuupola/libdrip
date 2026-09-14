#ifndef DRIP_ERROR_H
#define DRIP_ERROR_H

typedef enum {
    DRIP_SUCCESS = 0,
    DRIP_ERROR_NULL_POINTER = -1,
    DRIP_ERROR_BUFFER_TOO_SMALL = -2,
    DRIP_ERROR_BUFFER_TOO_LARGE = -3,
    DRIP_ERROR_ARRAY_OVERFLOW = -4,
    DRIP_ERROR_INVALID_INDEX = -5,
    DRIP_ERROR_CALLBACK_FAILED = -6,
    DRIP_ERROR_INVALID_LENGTH = -7,
    DRIP_ERROR_INVALID_SAM_TYPE = -8,
    DRIP_ERROR_OUT_OF_RANGE = -9,
    DRIP_ERROR_INVALID_IPV6_PREFIX = -10,
    DRIP_ERROR_VERIFICATION_FAILED = -11,
    DRIP_ERROR_INVALID_TIMESTAMP = -12,
    DRIP_ERROR_INVALID_CHILD_DET = -13,
    DRIP_ERROR_INVALID_PARENT_DET = -14,
    /* DRIP_ERROR_INVALID_HHSI = -15, */
    DRIP_ERROR_INVALID_IPV6_STRING = -16,
    /* DRIP_ERROR_INVALID_RAA = -17, */
    DRIP_ERROR_INVALID_DET = -18,
    DRIP_ERROR_TIMESTAMP_NOT_YET_VALID = -19,
    DRIP_ERROR_TIMESTAMP_EXPIRED = -20,
    DRIP_ERROR_INVALID_APEX_DELEGATION = -21,
    DRIP_ERROR_INVALID_RAA_DELEGATION = -22,
    DRIP_ERROR_INVALID_HDA_DELEGATION = -23,
} drip_error_t;

/**
 * @brief Convert error code to string representation.
 *
 * @param error The error code to convert.
 *
 * @return String representation of the error code.
 *         Returns "UNKNOWN" for invalid values.
 */
const char *drip_error_to_string(drip_error_t error);

#endif /* DRIP_ERROR_H */
