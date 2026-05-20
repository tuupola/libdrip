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
    uint8_t *signature,
    size_t signature_size,
    size_t *signature_length
) {
    (void)signature_size;
    const uint8_t *key = (const uint8_t *)context;
    unsigned long long sig_len = 0;
    int rc = crypto_sign_detached(signature, &sig_len, input, input_length, key);
    if (0 == rc) {
        *signature_length = (size_t)sig_len;
    }
    return rc;
}

int main(void) {
    drip_manifest_t manifest, decoded;
    uint8_t encoded[DRIP_MANIFEST_MAX_SIZE];
    size_t encoded_length;

    drip_manifest_init(&manifest);
    drip_manifest_set_vna_unixtime(&manifest, (uint32_t)time(NULL));
    drip_manifest_set_vnb_unixtime(&manifest, (uint32_t)time(NULL) + 120);
    drip_manifest_sign(&manifest, sign_ed25519, (void *)secret_key);

    drip_manifest_encode(&manifest, encoded, sizeof(encoded), &encoded_length);
    drip_manifest_decode(&decoded, encoded, sizeof(encoded));

    printf("Manifest:\n\n");
    hexdump(encoded, encoded_length);
    hexstring(encoded, encoded_length);

    char json[4096];
    printf("\n");
    drip_manifest_to_json(&manifest, json, sizeof(json));
    printf("%s\n\n", json);

    drip_manifest_to_json(&decoded, json, sizeof(json));
    printf("%s\n\n", json);

    return 0;
}
