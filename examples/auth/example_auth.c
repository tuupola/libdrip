#include <stdint.h>
#include <stdio.h>

#include "drip/manifest.h"

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

int main(void) {
    drip_manifest_t manifest;
    uint8_t encoded[256];
    size_t encoded_length;

    drip_manifest_init(&manifest);
    drip_manifest_encode(&manifest, encoded, sizeof(encoded), &encoded_length);

    hexdump(encoded, encoded_length);

    return 0;
}
