#include <stdio.h>
#include <string.h>

#include "drip/hash.h"

int drip_hash(
    const uint8_t *input,
    size_t input_length,
    drip_hash_t *hash,
    drip_hash_cb_t callback,
    void *context
) {
    if (input == NULL || hash == NULL || callback == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    size_t hash_length = 0;
    int rc = callback(context, input, input_length, (uint8_t *)hash, DRIP_HASH_SIZE, &hash_length);
    if (rc != 0) {
        return DRIP_ERROR_CALLBACK_FAILED;
    }

    return DRIP_SUCCESS;
}

int drip_hash_to_hex(const drip_hash_t *hash, char *hex, size_t hex_size) {
    if (hash == NULL || hex == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    if (hex_size < DRIP_HASH_SIZE * 2 + 1) {
        return DRIP_ERROR_BUFFER_TOO_SMALL;
    }

    snprintf(hex, hex_size, "%02x%02x%02x%02x%02x%02x%02x%02x", ((const uint8_t *)hash)[0], ((const uint8_t *)hash)[1], ((const uint8_t *)hash)[2], ((const uint8_t *)hash)[3], ((const uint8_t *)hash)[4], ((const uint8_t *)hash)[5], ((const uint8_t *)hash)[6], ((const uint8_t *)hash)[7]);

    return DRIP_SUCCESS;
}
