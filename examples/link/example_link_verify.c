#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sodium.h>

#include "drip/link.h"
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

/* Callback wrapper for libsodium */
static int verify_ed25519(
    void *context, const uint8_t *message, size_t message_length,
    const uint8_t *signature, size_t signature_length
) {
    (void)signature_length;
    const uint8_t *key = (const uint8_t *)context;
    return crypto_sign_verify_detached(signature, message, message_length, key);
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

    uint8_t buffer[DRIP_LINK_SIZE];
    int length = hex_to_bytes(hex_input, buffer, sizeof(buffer));
    if (length < 0) {
        fprintf(stderr, "Error: Invalid hex string\n");
        return 1;
    }

    drip_link_t link;
    rc = drip_link_decode(&link, buffer, (size_t)length);
    if (rc != 0) {
        fprintf(stderr, "Error: Failed to decode link\n");
        return 1;
    }

    rc = drip_link_verify(&link, verify_ed25519, (void *)public_key);

    if (0 == rc) {
        printf("\nSignature verified.\n\n");
    } else {
        printf("\nSignature verification failed.\n\n");
    }

    return 0;
}
