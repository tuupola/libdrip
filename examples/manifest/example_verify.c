#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sodium.h>

#include "drip/manifest.h"
#include "keys.h"

static int hex_to_bytes(const char *hex, uint8_t *bytes, size_t max_length) {
    size_t hex_length = strlen(hex);
    if (hex_length % 2 != 0) {
        return -1;
    }

    size_t byte_length = hex_length / 2;
    if (byte_length > max_length) {
        return -1;
    }

    for (size_t i = 0; i < byte_length; ++i) {
        unsigned int byte;
        if (sscanf(hex + 2 * i, "%2x", &byte) != 1) {
            return -1;
        }
        bytes[i] = (uint8_t)byte;
    }

    return (int)byte_length;
}

static void hexdump(const void *data, size_t size) {
    const uint8_t *bytes = (const uint8_t *)data;

    for (size_t i = 0; i < size; ++i) {
        if (i > 0 && i % 16 == 0) {
            printf("\n");
        } else if (i > 0 && i % 8 == 0) {
            printf(" ");
        }
        printf("%02x ", bytes[i]);
    }
    printf("\n\n");
}

/* Callback wrapper for libsodium */
static int verify_ed25519(
    void *context, const uint8_t *message, size_t message_len,
    const uint8_t *signature, size_t signature_length
) {
    (void)signature_length;
    const uint8_t *key = (const uint8_t *)context;
    return crypto_sign_verify_detached(signature, message, message_len, key);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <hex string>\n", argv[0]);
        return 1;
    }

    const char *hex_input = argv[1];
    int rc = 0;

    if (sodium_init() < 0) {
        return 1;
    }

    uint8_t buffer[DRIP_MANIFEST_MAX_SIZE + 1];
    int length = hex_to_bytes(hex_input, buffer, sizeof(buffer));
    if (length < 0) {
        fprintf(stderr, "Error: Invalid hex string\n");
        return 1;
    }

    drip_manifest_t manifest;
    rc = drip_manifest_decode(&manifest, buffer, length);
    if (rc != DRIP_SUCCESS) {
         fprintf(stderr, "Error: No auth message found\n");
         return 1;
    }

    rc = drip_manifest_verify(&manifest, verify_ed25519, (void *)public_key);

    if (0 == rc) {
        printf("\nSignature verified.\n\n");
    } else {
        printf("\nSignature verification failed.\n\n");
    }

    return 0;
}
