#ifndef DRIP_HASH_H
#define DRIP_HASH_H

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "drip/format.h"

#define DRIP_HASH_SIZE 8

typedef uint8_t drip_hash_t[DRIP_HASH_SIZE];

static_assert(sizeof(drip_hash_t) == DRIP_HASH_SIZE, "drip_hash_t size mismatch");

/**
 * @brief Callback function type for producing hashes.
 *
 * Called by drip_hash() to perform the actual hashing of the payload.
 *
 * @param context Opaque context passed to the callback.
 * @param input Pointer to the payload to hash.
 * @param input_length Length of the payload in bytes.
 * @param buffer Output buffer for the hash.
 * @param buffer_size Size of the hash buffer in bytes.
 * @param output_length Receives resulting hash length written.
 *
 * @retval 0 on success.
 * @retval Non-zero on hashing failure.
 */
typedef int (*drip_hash_cb_t)(
    void *context, const uint8_t *input, size_t input_length, uint8_t *buffer,
    size_t buffer_size, size_t *output_length
);

int drip_hash(
    const uint8_t *input, size_t input_length, drip_hash_t *hash, drip_hash_cb_t callback,
    void *context
);

int drip_hash_to_hex(const drip_hash_t *hash, char *hex, size_t hex_size);

#endif
