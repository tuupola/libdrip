#include "drip/error.h"

const char *drip_error_to_string(drip_error_t error) {
    switch (error) {
        case DRIP_SUCCESS:
            return "DRIP_SUCCESS";
        case DRIP_ERROR_NULL_POINTER:
            return "DRIP_ERROR_NULL_POINTER";
        case DRIP_ERROR_BUFFER_TOO_SMALL:
            return "DRIP_ERROR_BUFFER_TOO_SMALL";
        case DRIP_ERROR_BUFFER_TOO_LARGE:
            return "DRIP_ERROR_BUFFER_TOO_LARGE";
        case DRIP_ERROR_ARRAY_OVERFLOW:
            return "DRIP_ERROR_ARRAY_OVERFLOW";
        case DRIP_ERROR_INVALID_INDEX:
            return "DRIP_ERROR_INVALID_INDEX";
        case DRIP_ERROR_CALLBACK_FAILED:
            return "DRIP_ERROR_CALLBACK_FAILED";
        case DRIP_ERROR_INVALID_LENGTH:
            return "DRIP_ERROR_INVALID_LENGTH";
        case DRIP_ERROR_INVALID_SAM_TYPE:
            return "DRIP_ERROR_INVALID_SAM_TYPE";
        case DRIP_ERROR_OUT_OF_RANGE:
            return "DRIP_ERROR_OUT_OF_RANGE";
        case DRIP_ERROR_INVALID_IPV6_PREFIX:
            return "DRIP_ERROR_INVALID_IPV6_PREFIX";
        case DRIP_ERROR_VERIFICATION_FAILED:
            return "DRIP_ERROR_VERIFICATION_FAILED";
        case DRIP_ERROR_INVALID_TIMESTAMP:
            return "DRIP_ERROR_INVALID_TIMESTAMP";
        case DRIP_ERROR_INVALID_CHILD_DET:
            return "DRIP_ERROR_INVALID_CHILD_DET";
        case DRIP_ERROR_INVALID_PARENT_DET:
            return "DRIP_ERROR_INVALID_PARENT_DET";
        case DRIP_ERROR_INVALID_IPV6_STRING:
            return "DRIP_ERROR_INVALID_IPV6_STRING";
        case DRIP_ERROR_INVALID_DET:
            return "DRIP_ERROR_INVALID_DET";
        case DRIP_ERROR_TIMESTAMP_NOT_YET_VALID:
            return "DRIP_ERROR_TIMESTAMP_NOT_YET_VALID";
        case DRIP_ERROR_TIMESTAMP_EXPIRED:
            return "DRIP_ERROR_TIMESTAMP_EXPIRED";
        case DRIP_ERROR_INVALID_APEX_DELEGATION:
            return "DRIP_ERROR_INVALID_APEX_DELEGATION";
        case DRIP_ERROR_INVALID_RAA_DELEGATION:
            return "DRIP_ERROR_INVALID_RAA_DELEGATION";
        case DRIP_ERROR_INVALID_HDA_DELEGATION:
            return "DRIP_ERROR_INVALID_HDA_DELEGATION";
        default:
            return "UNKNOWN";
    }
}
