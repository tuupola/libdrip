#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sodium.h>

#include "drip/link.h"

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
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <parent hex> <child hex>\n", argv[0]);
        return 1;
    }

    if (sodium_init() < 0) {
        return 1;
    }

    drip_link_t parent_link, child_link;
    const drip_hi_t *parent_hi;

    const char *parent_hex = argv[1];
    const char *child_hex = argv[2];
    int rc = 0;
    int length = 0;

    uint8_t buffer[DRIP_LINK_SIZE];

    length = hex_to_bytes(parent_hex, buffer, sizeof(buffer));
    if (length != DRIP_LINK_SIZE) {
        fprintf(stderr, "Error: Link hex must be %d bytes\n", DRIP_LINK_SIZE);
        return 1;
    }

    rc = drip_link_decode(&parent_link, buffer, (size_t)length);
    if (rc != 0) {
        fprintf(stderr, "Error: Failed to decode parent link\n");
        return 1;
    }

    rc = drip_link_validate(&parent_link);
    if (rc != DRIP_SUCCESS) {
        fprintf(stderr, "Error: Parent link validation failed: %d\n", rc);
        return 1;
    }

    length = hex_to_bytes(child_hex, buffer, sizeof(buffer));
    if (length < 0) {
        fprintf(stderr, "Error: Invalid child hex string\n");
        return 1;
    }

    rc = drip_link_decode(&child_link, buffer, (size_t)length);
    if (rc != 0) {
        fprintf(stderr, "Error: Failed to decode child link\n");
        return 1;
    }

    rc = drip_link_validate(&child_link);
    if (rc != DRIP_SUCCESS) {
        fprintf(stderr, "Error: Child link validation failed: %d\n", rc);
        return 1;
    }

    /* TODO: This should be somewhere else. */
    if (memcmp(parent_link.child_det, child_link.parent_det, DRIP_DET_SIZE) != 0) {
        fprintf(stderr, "Error: Parent / Child DET mismatch\n");
        return 1;
    }

    parent_hi = drip_link_get_child_hi(&parent_link);
    rc = drip_link_verify(
        &child_link, (uint32_t)time(NULL), verify_ed25519, (void *)parent_hi
    );

    if (0 == rc) {
        printf("\nSignature verified.\n\n");
    } else {
        printf("\nSignature verification failed.\n\n");
        return 1;
    }

    return 0;
}
