#include <string.h>

#include "drip/hash.h"

int drip_hash(
    const uint8_t *input,
    size_t input_length,
    uint8_t *hash,
    size_t hash_size,
    drip_hash_cb_t callback,
    void *context
) {
    if (input == NULL || hash == NULL || callback == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    if (hash_size < DRIP_HASH_LEN) {
        return DRIP_ERROR_HASHING_FAILED;
    }

    size_t hash_length = 0;
    int rc = callback(context, input, input_length, hash, hash_size, &hash_length);
    if (rc != 0) {
        return DRIP_ERROR_HASHING_FAILED;
    }

    return DRIP_SUCCESS;
}
