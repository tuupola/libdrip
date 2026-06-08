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

    const char *parent_hex = argv[1];
    const char *child_hex = argv[2];
    int rc = 0;
    int length = 0;
    uint32_t now, vnb, vna;

    uint8_t buffer[DRIP_LINK_SIZE];

    length = hex_to_bytes(parent_hex, buffer, sizeof(buffer));
    if (length < 0) {
        fprintf(stderr, "Error: Invalid parent hex string\n");
        return 1;
    }

    rc = drip_link_decode(&parent_link, buffer, (size_t)length);
    if (rc != 0) {
        fprintf(stderr, "Error: Failed to decode parent link\n");
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

    now = (uint32_t)time(NULL);
    vnb = drip_link_get_vnb_unixtime(&child_link);
    vna = drip_link_get_vna_unixtime(&child_link);
    if (now < vnb || now > vna) {
        fprintf(stderr, "Error: Timestamp now=%u vnb=%u vna=%u\n", now, vnb, vna);
        return 1;
    }

    const drip_hi_t *child_hi = drip_link_get_child_hi(&parent_link);

    rc = drip_link_verify(&child_link, verify_ed25519, (void *)child_hi);

    if (0 == rc) {
        printf("\nSignature verified.\n\n");
    } else {
        printf("\nSignature verification failed.\n\n");
    }

    return 0;
}
