#ifndef DRIP_DET_H
#define DRIP_DET_H

#include <stddef.h>
#include <stdint.h>

#include "drip/format.h"
#include "drip/hash.h"

#define DRIP_DET_IPV6_PREFIX_STRING "2001:30::/28"
#define DRIP_DET_IPV6_STRING_SIZE 40

#define DRIP_DET_SIZE 16

typedef uint8_t drip_det_t[DRIP_DET_SIZE];

int drip_det_init(drip_det_t *det);

int drip_det_set_raa(drip_det_t *det, uint16_t raa);
uint16_t drip_det_get_raa(const drip_det_t *det);

int drip_det_set_hda(drip_det_t *det, uint16_t hda);
uint16_t drip_det_get_hda(const drip_det_t *det);

int drip_det_set_hid(drip_det_t *det, uint32_t hid);
uint32_t drip_det_get_hid(const drip_det_t *det);

int drip_det_set_hhsi(drip_det_t *det, uint8_t hhsi);
uint8_t drip_det_get_hhsi(const drip_det_t *det);

int drip_det_set_hash(drip_det_t *det, const drip_hash_t *hash);
const drip_hash_t *drip_det_get_hash(const drip_det_t *det);
int drip_det_update_hash(
    drip_det_t *det, const drip_hi_t *hi, drip_hash_cb_t callback, void *context
);

int drip_det_validate(const drip_det_t *det);
int drip_det_verify(
    const drip_det_t *det, const drip_hi_t *hi, drip_hash_cb_t callback, void *context
);

// int drip_det_to_ipv6_string(const drip_det_t *det, char *buffer, size_t buffer_size);
// int drip_det_from_ipv6_string(drip_det_t *det, const char *string);

#endif /* DRIP_DET_H */
