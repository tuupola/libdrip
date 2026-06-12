#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "drip/det.h"
#include "drip/hash.h"
#include "SP800-185.h"

/* clang-format off */
static const uint8_t DRIP_DET_CONTEXT_ID[16] = {
    0x00, 0xB5, 0xA6, 0x9C, 0x79, 0x5D, 0xF5, 0xD5,
    0xF0, 0x08, 0x7F, 0x56, 0x84, 0x3F, 0x2C, 0x40
};
/* clang-format on */

static void hex_string(const void *data, size_t size) {
    const uint8_t *p = data;
    while (size--) {
        printf("%02x", *p++);
    }
    printf("\n");
}

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

static int det_cshake128_cb(
    void *context, const uint8_t *input, size_t input_length, uint8_t *hash,
    size_t hash_size, size_t *hash_length
) {
    (void)context;
    int rc = cSHAKE128(
        input, input_length * 8, hash, hash_size * 8, NULL, 0, DRIP_DET_CONTEXT_ID,
        sizeof(DRIP_DET_CONTEXT_ID) * 8
    );
    if (rc != 0) {
        return rc;
    }

    *hash_length = hash_size;
    return 0;
}

int main(int argc, char *argv[]) {
    char *endptr;
    long raa, hda;
    int length, rc;

    drip_hi_t hi;
    drip_det_t det;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <raa> <hda> <hi_hex>\n", argv[0]);
        return 1;
    }

    errno = 0;
    raa = strtol(argv[1], &endptr, 10);
    if (errno != 0 || *endptr != '\0') {
        fprintf(stderr, "Error: Invalid RAA value\n");
        return 1;
    }

    hda = strtol(argv[2], &endptr, 10);
    if (errno != 0 || *endptr != '\0') {
        fprintf(stderr, "Error: Invalid HDA value\n");
        return 1;
    }

    length = hex_to_bytes(argv[3], hi, sizeof(hi));
    if (length < 0) {
        fprintf(stderr, "Error: Invalid hex string\n");
        return 1;
    }

    if (length != DRIP_HI_SIZE) {
        fprintf(stderr, "Error: Hex string must be %d bytes\n", DRIP_HI_SIZE);
        return 1;
    }

    rc = drip_det_init(&det);
    if (rc != DRIP_SUCCESS) {
        fprintf(stderr, "Error: Failed to initialize det\n");
        return 1;
    }

    rc = drip_det_set_raa(&det, (uint16_t)raa);
    if (rc != DRIP_SUCCESS) {
        fprintf(stderr, "Error: Invalid RAA value\n");
        return 1;
    }

    rc = drip_det_set_hda(&det, (uint16_t)hda);
    if (rc != DRIP_SUCCESS) {
        fprintf(stderr, "Error: Invalid HDA value\n");
        return 1;
    }

    /* We only support 5 atm */
    drip_det_set_hhsi(&det, 5);

    rc = drip_det_update_hash(&det, &hi, det_cshake128_cb, NULL);
    if (rc != DRIP_SUCCESS) {
        fprintf(stderr, "Error: Failed to update hash: %d\n", rc);
        return 1;
    }

    printf("DET: ");
    hex_string(det, DRIP_DET_SIZE);

    return 0;
}
