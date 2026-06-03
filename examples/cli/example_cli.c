#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "drip/format.h"
#include "drip/link.h"
#include "drip/manifest.h"

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

static void strip_newline(char *str) {
    size_t length = strlen(str);
    if (length > 0 && str[length - 1] == '\n') {
        str[length - 1] = '\0';
    }
}

static int decode_and_print(const char *hex_string, int force) {
    int rc;
    char json[4096];

    uint8_t buffer[DRIP_MANIFEST_MAX_SIZE];
    int length = hex_to_bytes(hex_string, buffer, sizeof(buffer));
    if (length < 0) {
        fprintf(stderr, "Error: Invalid hex string\n");
        return 1;
    }

    uint8_t sam_type = buffer[0];

    if (sam_type == DRIP_SAM_TYPE_LINK) {
        if (length != DRIP_LINK_SIZE) {
            fprintf(stderr, "Error: Expected %d bytes for LINK, got %d\n", DRIP_LINK_SIZE, length);
            return 1;
        }

        drip_link_t link;
        memcpy(&link, buffer, sizeof(link));

        rc = drip_link_to_json(&link, json, sizeof(json));
        if (rc < 0) {
            fprintf(stderr, "Error: %d\n", rc);
            return 1;
        }
    } else if (sam_type == DRIP_SAM_TYPE_MANIFEST) {
        if (length < DRIP_MANIFEST_MIN_SIZE) {
            fprintf(stderr, "Error: Expected at least %d bytes, got %d\n", DRIP_MANIFEST_MIN_SIZE, length);
            return 1;
        }

        if (length > DRIP_MANIFEST_MAX_SIZE) {
            fprintf(stderr, "Error: Expected at most %d bytes, got %d\n", DRIP_MANIFEST_MAX_SIZE, length);
            return 1;
        }

        drip_manifest_t manifest;
        rc = drip_manifest_decode(&manifest, buffer, length);
        if (rc < 0) {
            fprintf(stderr, "Error: %d\n", rc);
            return 1;
        }

        rc = drip_manifest_to_json(&manifest, json, sizeof(json));
        if (rc < 0) {
            fprintf(stderr, "Error: %d\n", rc);
            return 1;
        }
    } else {
        fprintf(stderr, "Error: Unsupported SAM type: 0x%02x\n", sam_type);
        return 1;
    }

    printf("%s\n", json);
    fflush(stdout);

    return 0;
}

int main(int argc, char *argv[]) {
    char hex_input[512];
    const char *hex_string = NULL;

    int force = 0;
    int hex_arg_index = 1;

    /* Handle --help / -h and --force / -f */
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            printf("Usage: %s [-f|--force] [<hex_string>]\n", argv[0]);
            return 0;
        } else if (strcmp(argv[i], "--force") == 0 || strcmp(argv[i], "-f") == 0) {
            force = 1;
        } else {
            hex_arg_index = i;
        }
    }

    /* Determine hex_string source */
    if (hex_arg_index >= 1 && hex_arg_index < argc) {
        hex_string = argv[hex_arg_index];
    } else if (argc > 2 && hex_arg_index == 1) {
        fprintf(stderr, "Usage: %s [-f|--force] [<hex_string>]\n", argv[0]);
        return 1;
    }

    /* If hex_string provided, decode and exit */
    if (hex_string != NULL) {
        return decode_and_print(hex_string, force);
    }

    /* Read hex strings from stdin in a loop */
    while (fgets(hex_input, sizeof(hex_input), stdin) != NULL) {
        strip_newline(hex_input);
        if (hex_input[0] == '\0') {
            continue;
        }
        decode_and_print(hex_input, force);
    }

    return 0;
}
