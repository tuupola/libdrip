#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "drip/det.h"
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
    int length, rc;

    drip_det_t det;
    drip_hi_t hi;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <det_hex> <hi_hex>\n", argv[0]);
        return 1;
    }

    length = hex_to_bytes(argv[1], (uint8_t *)&det, sizeof(det));
    if (length < 0) {
        fprintf(stderr, "Error: Invalid DET hex string\n");
        return 1;
    }

    if (length != DRIP_DET_SIZE) {
        fprintf(stderr, "Error: DET hex string must be %d bytes\n", DRIP_DET_SIZE);
        return 1;
    }

    length = hex_to_bytes(argv[2], (uint8_t *)&hi, sizeof(hi));
    if (length < 0) {
        fprintf(stderr, "Error: Invalid HI hex string\n");
        return 1;
    }

    if (length != DRIP_HI_SIZE) {
        fprintf(stderr, "Error: HI hex string must be %d bytes\n", DRIP_HI_SIZE);
        return 1;
    }

    printf("DET: ");
    hex_string(&det, DRIP_DET_SIZE);

    rc = drip_det_verify(&det, &hi, det_cshake128_cb, NULL);
    if (rc == DRIP_SUCCESS) {
        printf("Verification: OK\n");
        return 0;
    } else if (rc == DRIP_ERROR_VERIFICATION_FAILED) {
        printf("Verification: FAILED\n");
        return 1;
    } else {
        printf("Error: verification error: %d\n", rc);
        return 1;
    }
}
