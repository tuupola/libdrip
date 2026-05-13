#ifndef DRIP_HASH_H
#define DRIP_HASH_H

#include <stddef.h>
#include <stdint.h>

#define DRIP_HASH_LEN 8

typedef uint8_t drip_hash_t[DRIP_HASH_LEN];

/**
 * @brief Callback function type for producing manifest hashes.
 *
 * Called by drip_manifest_hash() to perform the actual hashing of the payload.
 *
 * @param context Opaque context passed to the callback.
 * @param input Pointer to the payload to hash.
 * @param input_length Length of the payload in bytes.
 * @param hash Output buffer for the hash.
 * @param hash_size Size of the hash buffer in bytes.
 * @param hash_length Output: actual hash length written.
 *
 * @retval 0 on success.
 * @retval Non-zero on hashing failure.
 */
typedef int (*drip_hash_cb_t)(
    void *context,
    const uint8_t *input,
    size_t input_length,
    uint8_t *hash,
    size_t hash_size,
    size_t *hash_length
);

int drip_hash(
    const uint8_t *input,
    size_t input_length,
    uint8_t *hash,
    size_t hash_size,
    drip_hash_cb_t callback,
    void *context
);

#endif
