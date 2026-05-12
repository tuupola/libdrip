#ifndef DRIP_MANIFEST_H
#define DRIP_MANIFEST_H

#include <stddef.h>
#include <stdint.h>

#define DRIP_SAM_TYPE_MANIFEST 3
#define DRIP_DET_LEN 16
#define DRIP_SIGNATURE_LEN 64
#define DRIP_HASH_LEN 8
#define DRIP_MANIFEST_ASTM_MAX 11
#define DRIP_AUTH_DATA_MAX 201

typedef enum {
    DRIP_SUCCESS = 0,
    DRIP_ERROR_NULL_POINTER = -1,
    DRIP_ERROR_BUFFER_TOO_SMALL = -2,
} drip_status_t;

typedef uint8_t drip_det_t[DRIP_DET_LEN];
typedef uint8_t drip_sig_t[DRIP_SIGNATURE_LEN];
typedef uint8_t drip_hash_t[DRIP_HASH_LEN];

typedef struct drip_manifest {
    uint8_t sam_type;

    uint32_t vnb;
    uint32_t vna;

    drip_hash_t previous_manifest;
    drip_hash_t current_manifest;
    drip_hash_t drip_link;

    uint8_t astm_hash_count;
    drip_hash_t astm_hashes[DRIP_MANIFEST_ASTM_MAX];

    drip_det_t det;
    drip_sig_t signature;
} drip_manifest_t;

int drip_manifest_init(drip_manifest_t *manifest);

uint32_t drip_manifest_get_vnb(const drip_manifest_t *manifest);
int drip_manifest_set_vnb(drip_manifest_t *manifest, uint32_t vnb);

#endif
