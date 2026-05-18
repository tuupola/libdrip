#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "drip/manifest.h"
#include "rid/auth.h"
#include "rid/message_pack.h"

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

int main(void) {
    drip_manifest_t manifest;
    uint8_t encoded[256];
    size_t encoded_length;
    rid_auth_t auth;
    uint8_t signature[256];
    rid_message_pack_t pack;

    drip_manifest_init(&manifest);
    drip_manifest_set_vna_unixtime(&manifest, (uint32_t)time(NULL));
    drip_manifest_set_vnb_unixtime(&manifest, (uint32_t)time(NULL) + 120);
    drip_manifest_encode(&manifest, encoded, sizeof(encoded), &encoded_length);

    printf("Manifest:\n");
    hexdump(encoded, encoded_length);

    rid_auth_init(&auth);
    rid_auth_set_type(&auth, RID_AUTH_TYPE_SPECIFIC_METHOD);
    rid_auth_set_unixtime(&auth, (uint32_t)time(NULL));
    rid_auth_set_signature(&auth, encoded, encoded_length);
    rid_auth_get_signature(&auth, signature, sizeof(signature));

    printf("Auth type:  %d\n", rid_auth_get_type(&auth));
    printf("Timestamp:  %u\n", rid_auth_get_timestamp(&auth));
    printf("Length:     %d bytes\n\n", rid_auth_get_length(&auth));
    printf("Page count: %d\n", rid_auth_get_page_count(&auth));

    printf("\nSignature:\n");
    hexdump(signature, encoded_length);

    printf("Auth pages:\n");
    uint8_t page_count = rid_auth_get_page_count(&auth);
    for (uint8_t i = 0; i < page_count; i++) {
        printf("Page %d:\n", i);
        if (i == 0) {
            hexdump(&auth.page_0, sizeof(auth.page_0));
        } else {
            hexdump(&auth.page_x[i - 1], sizeof(auth.page_x[0]));
        }
    }

    rid_message_pack_init(&pack);
    rid_message_pack_set_auth(&pack, &auth);

    printf("Message pack:\n");
    hexdump(&pack, rid_message_pack_get_size(&pack));
    hexstring(&pack, rid_message_pack_get_size(&pack));

    return 0;
}
