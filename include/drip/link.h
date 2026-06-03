#ifndef DRIP_LINK_H
#define DRIP_LINK_H

#include <stddef.h>
#include <stdint.h>

#include "drip/format.h"

#define DRIP_LINK_SIZE 137

typedef int (*drip_link_sign_cb_t)(
    void *context,
    const uint8_t *input,
    size_t input_length,
    uint8_t *signature,
    size_t signature_size,
    size_t *signature_length
);

typedef int (*drip_link_verify_cb_t)(
    void *context,
    const uint8_t *input,
    size_t input_length,
    const uint8_t *signature,
    size_t signature_length
);

typedef struct __attribute__((__packed__)) drip_link {
    uint8_t sam_type;

    uint32_t vnb;
    uint32_t vna;

    drip_det_t child_det;
    drip_hi_t child_hi;
    drip_det_t parent_det;

    drip_signature_t signature;
} drip_link_t;

int drip_link_init(drip_link_t *link);

uint32_t drip_link_get_vnb(const drip_link_t *link);
int drip_link_set_vnb(drip_link_t *link, uint32_t vnb);

uint32_t drip_link_get_vna(const drip_link_t *link);
int drip_link_set_vna(drip_link_t *link, uint32_t vna);

int drip_link_set_vna_unixtime(drip_link_t *link, uint32_t unixtime);
uint32_t drip_link_get_vna_unixtime(const drip_link_t *link);

int drip_link_set_vnb_unixtime(drip_link_t *link, uint32_t unixtime);
uint32_t drip_link_get_vnb_unixtime(const drip_link_t *link);

const drip_det_t *drip_link_get_child_det(const drip_link_t *link);
int drip_link_set_child_det(drip_link_t *link, const drip_det_t *det);

const drip_hi_t *drip_link_get_child_hi(const drip_link_t *link);
int drip_link_set_child_hi(drip_link_t *link, const drip_hi_t *hi);

const drip_det_t *drip_link_get_parent_det(const drip_link_t *link);
int drip_link_set_parent_det(drip_link_t *link, const drip_det_t *det);

const drip_signature_t *drip_link_get_signature(const drip_link_t *link);
int drip_link_set_signature(drip_link_t *link, const drip_signature_t *signature);

int drip_link_decode(drip_link_t *link, const uint8_t *buffer, size_t buffer_size);
int drip_link_encode(const drip_link_t *link, uint8_t *buffer, size_t buffer_size, size_t *encoded_length);

int drip_link_sign(
    drip_link_t *link,
    drip_link_sign_cb_t callback,
    void *context
);

int drip_link_verify(
    drip_link_t *link,
    drip_link_verify_cb_t callback,
    void *context
);

int drip_link_to_json(
    const drip_link_t *link,
    char *buffer,
    size_t buffer_size
);

#endif /* DRIP_LINK_H */
