#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include <sodium.h>

#include "drip/manifest.h"
#include "keys.h"

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

static void hexstring(const void *data, size_t size) {
    const uint8_t *p = data;
    while (size--) {
        printf("%02x", *p++);
    }
    printf("\n");
}

/* Callback wrapper for libsodium */
static int sign_ed25519(
    void *context,
    const uint8_t *input,
    size_t input_length,
    uint8_t *buffer,
    size_t buffer_size,
    size_t *output_length
) {
    (void)buffer_size;
    const uint8_t *key = (const uint8_t *)context;
    unsigned long long sig_len = 0;
    int rc = crypto_sign_detached(buffer, &sig_len, input, input_length, key);
    if (0 == rc) {
        *output_length = (size_t)sig_len;
    }
    return rc;
}

int main(void) {
    drip_manifest_t manifest;
    drip_hash_t hash = {0xDE, 0xAD, 0xBE, 0xEF, 0xDE, 0xAD, 0xBE, 0xEF};
    /* RFC 9374 example DET 2001:30:280:1405:a3ad:1952:ad0:a69e */
    drip_det_t det = {
        0x20, 0x01, 0x00, 0x30, 0x02, 0x80, 0x14, 0x05,
        0xa3, 0xad, 0x19, 0x52, 0x0a, 0xd0, 0xa6, 0x9e
    };

    uint8_t encoded[DRIP_MANIFEST_MAX_SIZE];

    size_t encoded_length;
    int rc;

    drip_manifest_init(&manifest);
    drip_manifest_set_vnb_unixtime(&manifest, (uint32_t)time(NULL));
    drip_manifest_set_vna_unixtime(&manifest, (uint32_t)time(NULL) + 120);
    drip_manifest_set_det(&manifest, &det);
    drip_manifest_add_evidence(&manifest, &hash);

    rc = drip_manifest_validate(&manifest);
    if (rc != DRIP_SUCCESS) {
        fprintf(stderr, "Error: Manifest validation failed (%d)\n", rc);
        return 1;
    }

    drip_manifest_sign(&manifest, sign_ed25519, (void *)secret_key);
    drip_manifest_encode(&manifest, encoded, sizeof(encoded), &encoded_length);

    printf("Manifest:\n\n");
    hexdump(encoded, encoded_length);
    hexstring(encoded, encoded_length);

    char json[4096];
    printf("\n");
    drip_manifest_to_json(&manifest, json, sizeof(json), NULL);
    printf("%s\n\n", json);

    printf("Verify with:\n");
    printf("$ ./manifest_verify ");
    hexstring(&encoded, encoded_length);
    printf("\n");

    return 0;
}
