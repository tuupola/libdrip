#include <string.h>

#include "drip/det.h"
#include "drip/format.h"

/*
 *   +------------+---------+---------+--------+------------------+
 *   |  28 bits   | 14 bits | 14 bits | 8 bits |     64 bits      |
 *   +------------+---------+---------+--------+------------------+
 *   | IPv6 Prefix|   RAA   |   HDA   |  HHSI  |   ORCHID hash    |
 *   +------------+---------+---------+--------+------------------+
 *   | IPv6 Prefix|        HID        |  HHSI  |   ORCHID hash    |
 *   +------------+---------+---------+--------+------------------+
 */

int drip_det_init(drip_det_t *det) {
    if (det == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    memset(det, 0, sizeof(drip_det_t));

    /* Add the DET IPv6 prefix 2001:30::/28 */
    (*det)[0] = 0x20;
    (*det)[1] = 0x01;
    (*det)[2] = 0x00;
    (*det)[3] = 0x30;

    return DRIP_SUCCESS;
}

int drip_det_set_raa(drip_det_t *det, uint16_t raa) {
    if (det == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    if (raa > 0x3FFF) {
        return DRIP_ERROR_OUT_OF_RANGE;
    }

    (*det)[3] = ((*det)[3] & 0xF0) | ((raa >> 10) & 0x0F);
    (*det)[4] = (uint8_t)((raa >> 2) & 0xFF);
    (*det)[5] = ((*det)[5] & 0x3F) | (uint8_t)((raa << 6) & 0xC0);

    return DRIP_SUCCESS;
}

uint16_t drip_det_get_raa(const drip_det_t *det) {
    if (det == NULL) {
        return 0;
    }

    return ((uint16_t)((*det)[3] & 0x0F) << 10) | ((uint16_t)(*det)[4] << 2) |
        ((uint16_t)((*det)[5] >> 6) & 0x03);
}

int drip_det_set_hda(drip_det_t *det, uint16_t hda) {
    if (det == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    if (hda > 0x3FFF) {
        return DRIP_ERROR_OUT_OF_RANGE;
    }

    (*det)[5] = ((*det)[5] & 0xC0) | ((hda >> 8) & 0x3F);
    (*det)[6] = (uint8_t)(hda & 0xFF);

    return DRIP_SUCCESS;
}

uint16_t drip_det_get_hda(const drip_det_t *det) {
    if (det == NULL) {
        return 0;
    }

    return ((uint16_t)((*det)[5] & 0x3F) << 8) | (uint16_t)(*det)[6];
}

int drip_det_set_hid(drip_det_t *det, uint32_t hid) {
    if (det == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    if (hid > 0x0FFFFFFF) {
        return DRIP_ERROR_OUT_OF_RANGE;
    }

    (*det)[3] = ((*det)[3] & 0xF0) | ((hid >> 24) & 0x0F);
    (*det)[4] = (uint8_t)((hid >> 16) & 0xFF);
    (*det)[5] = (uint8_t)((hid >> 8) & 0xFF);
    (*det)[6] = (uint8_t)(hid & 0xFF);

    return DRIP_SUCCESS;
}

uint32_t drip_det_get_hid(const drip_det_t *det) {
    if (det == NULL) {
        return 0;
    }

    return ((uint32_t)((*det)[3] & 0x0F) << 24) | ((uint32_t)(*det)[4] << 16) |
        ((uint32_t)(*det)[5] << 8) | (uint32_t)(*det)[6];
}

int drip_det_set_hhsi(drip_det_t *det, uint8_t hhsi) {
    if (det == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    (*det)[7] = hhsi;

    return DRIP_SUCCESS;
}

uint8_t drip_det_get_hhsi(const drip_det_t *det) {
    if (det == NULL) {
        return 0;
    }

    return (*det)[7];
}

int drip_det_set_hash(drip_det_t *det, const drip_hash_t *hash) {
    if (det == NULL || hash == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    memcpy(&(*det)[8], hash, sizeof(drip_hash_t));

    return DRIP_SUCCESS;
}

const drip_hash_t *drip_det_get_hash(const drip_det_t *det) {
    if (det == NULL) {
        return NULL;
    }

    return (const drip_hash_t *)&(*det)[8];
}

int drip_det_update_hash(
    drip_det_t *det, const drip_hi_t *hi, drip_hash_cb_t callback, void *context
) {
    int rc;
    uint8_t input[8 + sizeof(drip_hi_t)]; /* Not VLA */
    drip_hash_t hash;

    if (det == NULL || hi == NULL || callback == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    memcpy(&input[0], &(*det)[0], 8); /* Prefix|HID|HHSI */
    memcpy(&input[8], hi, sizeof(drip_hi_t)); /* HOST_ID */

    rc = drip_hash(input, sizeof(input), &hash, callback, context);
    if (rc != DRIP_SUCCESS) {
        return rc;
    }
    return drip_det_set_hash(det, &hash);
}

int drip_det_validate(const drip_det_t *det) {
    if (det == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }
    if ((*det)[0] != 0x20 || (*det)[1] != 0x01 || (*det)[2] != 0x00 ||
        ((*det)[3] & 0xF0) != 0x30) {
        return DRIP_ERROR_INVALID_IPV6_PREFIX;
    }
    return DRIP_SUCCESS;
}

int drip_det_verify(
    const drip_det_t *det, const drip_hi_t *hi, drip_hash_cb_t callback, void *context
) {
    int rc;
    uint8_t input[8 + sizeof(drip_hi_t)]; /* Not VLA */
    drip_hash_t hash;
    const drip_hash_t *current;

    if (det == NULL || hi == NULL || callback == NULL) {
        return DRIP_ERROR_NULL_POINTER;
    }

    memcpy(&input[0], &(*det)[0], 8); /* Prefix|HID|HHSI */
    memcpy(&input[8], hi, sizeof(drip_hi_t)); /* HOST_ID */

    rc = drip_hash(input, sizeof(input), &hash, callback, context);
    if (rc != DRIP_SUCCESS) {
        return rc;
    }

    current = drip_det_get_hash(det);
    if (memcmp(current, &hash, sizeof(drip_hash_t)) != 0) {
        return DRIP_ERROR_VERIFICATION_FAILED;
    }

    return DRIP_SUCCESS;
}
