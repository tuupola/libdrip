#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <sodium.h>

#include "drip/link.h"
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
    unsigned long long temp = 0;
    int rc = crypto_sign_detached(signature, &temp, input, input_length, key);
    if (0 == rc) {
        *signature_length = (size_t)temp;
    }
    return rc;
}

int main(void) {
    drip_link_t link;

    drip_link_init(&link);
    drip_link_set_vnb_unixtime(&link, 1767052800); /* 1.1.2026 */
    drip_link_set_vna_unixtime(&link, 1924905599); /* 31.12.2030 */

    drip_det_t child_det;
    drip_hi_t child_hi;
    drip_det_t parent_det;
    memset(&child_det, 0x11, sizeof(child_det));
    memset(&child_hi, 0x22, sizeof(child_hi));
    memset(&parent_det, 0x33, sizeof(parent_det));
    drip_link_set_child_det(&link, &child_det);
    drip_link_set_child_hi(&link, &child_hi);
    drip_link_set_parent_det(&link, &parent_det);

    drip_link_sign(&link, sign_ed25519, (void *)secret_key);

    uint8_t encoded[DRIP_LINK_SIZE];
    size_t encoded_length;
    drip_link_encode(&link, encoded, sizeof(encoded), &encoded_length);

    printf("Link:\n\n");
    hexdump(encoded, encoded_length);
    hexstring(encoded, encoded_length);

    char json[4096];
    printf("\n");
    drip_link_to_json(&link, json, sizeof(json));
    printf("%s\n\n", json);

    printf("Verify with:\n");
    printf("$ ./example_link_verify ");
    hexstring(encoded, sizeof(encoded));
    printf("\n");

    return 0;
}
