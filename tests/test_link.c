#include <sodium.h>
#include <stdint.h>
#include <string.h>

#include "drip/format.h"
#include "drip/link.h"
#include "SP800-185.h"
#include "unit.h"

/* clang-format off */
static const uint8_t public_key[32] = {
    0x6d, 0x92, 0x2c, 0x09, 0x2e, 0x55, 0x40, 0x86,
    0x49, 0x9f, 0x5d, 0x44, 0xf2, 0x02, 0xd4, 0x0a,
    0xde, 0x8e, 0x51, 0xb2, 0xcf, 0x0b, 0xb3, 0x44,
    0x5e, 0xa8, 0xaa, 0x4b, 0x15, 0xfb, 0x2e, 0x5e
};

static const uint8_t secret_key[64] = {
    0x7a, 0xb8, 0x0e, 0xb4, 0x90, 0xc3, 0x58, 0x2d,
    0x2c, 0xb3, 0x30, 0xed, 0x53, 0xae, 0x62, 0xe9,
    0x0d, 0x82, 0x99, 0xe1, 0xb1, 0xb9, 0x1c, 0xc7,
    0x50, 0xe3, 0xe0, 0xb5, 0xc0, 0xe9, 0x83, 0x09,
    0x6d, 0x92, 0x2c, 0x09, 0x2e, 0x55, 0x40, 0x86,
    0x49, 0x9f, 0x5d, 0x44, 0xf2, 0x02, 0xd4, 0x0a,
    0xde, 0x8e, 0x51, 0xb2, 0xcf, 0x0b, 0xb3, 0x44,
    0x5e, 0xa8, 0xaa, 0x4b, 0x15, 0xfb, 0x2e, 0x5e
};
/* clang-format on */

static int sign_ed25519(
    void *context, const uint8_t *input, size_t input_length, uint8_t *buffer,
    size_t buffer_size, size_t *output_length
) {
    (void)buffer_size;
    const uint8_t *key = (const uint8_t *)context;
    unsigned long long sig_len = 0;
    int rc = crypto_sign_detached(buffer, &sig_len, input, input_length, key);
    if (0 == rc) {
        *output_length = (size_t)sig_len;
    }
    return rc;
}

static int verify_ed25519(
    void *context, const uint8_t *message, size_t message_len, const uint8_t *signature,
    size_t signature_length
) {
    (void)signature_length;
    const uint8_t *key = (const uint8_t *)context;
    return crypto_sign_verify_detached(signature, message, message_len, key);
}

static int dummy_hash_cb(
    void *context, const uint8_t *input, size_t input_length, uint8_t *buffer,
    size_t buffer_size, size_t *output_length
) {
    (void)context;
    (void)buffer_size;
    size_t len = input_length < DRIP_HASH_SIZE ? input_length : DRIP_HASH_SIZE;
    memcpy(buffer, input, len);
    *output_length = DRIP_HASH_SIZE;
    return 0;
}

static int failing_hash_cb(
    void *context, const uint8_t *input, size_t input_length, uint8_t *buffer,
    size_t buffer_size, size_t *output_length
) {
    (void)context;
    (void)input;
    (void)input_length;
    (void)buffer;
    (void)buffer_size;
    (void)output_length;
    return -1;
}

static int dummy_verify_cb(
    void *context, const uint8_t *message, size_t message_len, const uint8_t *signature,
    size_t signature_length
) {
    (void)context;
    (void)message;
    (void)message_len;
    (void)signature;
    (void)signature_length;
    return 0;
}

/* clang-format off */
static const uint8_t DRIP_DET_CONTEXT_ID[16] = {
    0x00, 0xB5, 0xA6, 0x9C, 0x79, 0x5D, 0xF5, 0xD5,
    0xF0, 0x08, 0x7F, 0x56, 0x84, 0x3F, 0x2C, 0x40
};

/* https://github.com/tuupola/drip-scripts/tree/testing/testing */
/* hda16376-16376I.eds with SAM type 0x01 prepended */
static const uint8_t hda16376_16376i[] = {
    0x01, 0x80, 0x0b, 0x2b, 0x0d, 0x00, 0x21, 0xec, 0x10, 0x20, 0x01, 0x00,
    0x3f, 0xfe, 0x3f, 0xf8, 0x05, 0x0a, 0x8f, 0x96, 0xa9, 0xd7, 0x52, 0x5c,
    0x19, 0xa4, 0x92, 0xe2, 0x03, 0x98, 0x27, 0x37, 0x7a, 0xa4, 0xd0, 0xa8,
    0xb7, 0x57, 0x04, 0x8d, 0x55, 0xe4, 0x56, 0xff, 0x49, 0xf6, 0xa9, 0xb3,
    0x19, 0xe4, 0x0b, 0xbd, 0x01, 0x65, 0x65, 0x09, 0xc8, 0x20, 0x01, 0x00,
    0x3f, 0xfe, 0x3f, 0xf8, 0x05, 0x03, 0x25, 0xd3, 0x4f, 0x5a, 0x5a, 0xd1,
    0x86, 0xa0, 0xde, 0x89, 0xea, 0xf6, 0x33, 0xf2, 0xd3, 0x75, 0x2d, 0x9a,
    0x70, 0xb8, 0xdb, 0xa3, 0x5e, 0xa2, 0x44, 0x4a, 0xaf, 0x7c, 0xbc, 0x7e,
    0x48, 0x08, 0x82, 0x3c, 0x81, 0xae, 0xef, 0xf5, 0x95, 0x3b, 0xb3, 0x73,
    0xe0, 0x1d, 0xb7, 0x84, 0x24, 0x60, 0xc8, 0xe9, 0xec, 0x91, 0x42, 0xd8,
    0xeb, 0x62, 0x99, 0x53, 0xbe, 0xd4, 0x22, 0x55, 0x40, 0x36, 0x4f, 0x4b,
    0xe6, 0xa8, 0x02, 0xf9, 0x03,
};

/* https://github.com/tuupola/drip-scripts/tree/testing/testing */
/* ua1-16376-16376.eds with SAM type 0x01 prepended */
static const uint8_t ua1_16376_16376[] = {
    0x01, 0x80, 0x0b, 0x2b, 0x0d, 0x80, 0xed, 0x0a, 0x0f, 0x20, 0x01, 0x00,
    0x3f, 0xfe, 0x3f, 0xf8, 0x05, 0x22, 0x87, 0x9e, 0x75, 0x92, 0xf2, 0xd1,
    0x55, 0xb4, 0x11, 0x76, 0xc5, 0xb3, 0x05, 0xe1, 0x82, 0x3a, 0x47, 0x71,
    0x5c, 0x39, 0x8f, 0x57, 0x5d, 0xcc, 0x2a, 0x4f, 0x16, 0xbb, 0xde, 0xeb,
    0xdc, 0x42, 0xd6, 0x51, 0x89, 0x07, 0xf2, 0x3b, 0x72, 0x20, 0x01, 0x00,
    0x3f, 0xfe, 0x3f, 0xf8, 0x05, 0x0a, 0x8f, 0x96, 0xa9, 0xd7, 0x52, 0x5c,
    0x19, 0x24, 0x21, 0xd6, 0x25, 0xac, 0xa0, 0xc4, 0x54, 0xf2, 0x37, 0x47,
    0xb0, 0x1d, 0xca, 0x51, 0xc1, 0x94, 0x88, 0x34, 0x44, 0xf5, 0x9d, 0x90,
    0xcd, 0xaa, 0x7d, 0x07, 0x02, 0x2e, 0xfd, 0x76, 0xc9, 0xbd, 0x74, 0x49,
    0xb3, 0x8b, 0x87, 0x59, 0x56, 0x19, 0x86, 0x1d, 0xde, 0x4a, 0x86, 0x91,
    0x0e, 0x3b, 0xef, 0xcd, 0x96, 0x94, 0x8a, 0x1c, 0x40, 0x42, 0xb6, 0x33,
    0x8e, 0xd7, 0x21, 0xea, 0x09,
};

/* https://github.com/tuupola/drip-scripts/tree/testing/testing */
/* raa16376.eds with SAM type 0x01 prepended */
static const uint8_t raa16376[] = {
    0x01, 0x80, 0x0b, 0x2b, 0x0d, 0x80, 0xd9, 0xaf, 0x14, 0x20, 0x01, 0x00,
    0x3f, 0xfe, 0x00, 0x00, 0x05, 0x4f, 0xb8, 0x7c, 0x27, 0x28, 0x10, 0x70,
    0x48, 0x3f, 0xbe, 0x40, 0xd4, 0xd5, 0xc1, 0xe5, 0x8c, 0x5e, 0x80, 0xee,
    0x49, 0xf3, 0x67, 0x1a, 0xdd, 0xe1, 0xb4, 0x85, 0x12, 0xd5, 0x93, 0xc9,
    0xbc, 0xff, 0x6b, 0xf3, 0x69, 0xca, 0x66, 0xcc, 0x1f, 0x20, 0x01, 0x00,
    0x3f, 0xfe, 0x00, 0x00, 0x05, 0x4f, 0xb8, 0x7c, 0x27, 0x28, 0x10, 0x70,
    0x48, 0x12, 0x81, 0xeb, 0x8d, 0x57, 0xfd, 0xe4, 0x78, 0x0e, 0xdb, 0xe7,
    0x9f, 0x4c, 0x5c, 0x63, 0xab, 0x2f, 0xa6, 0x79, 0x87, 0xf9, 0xdb, 0x94,
    0x05, 0xbf, 0x7b, 0x59, 0x83, 0xd2, 0xda, 0x9a, 0x77, 0xaa, 0xf6, 0x7f,
    0x1d, 0x6b, 0x58, 0xf3, 0xcb, 0x15, 0x14, 0xc2, 0x7d, 0x16, 0x6b, 0xe3,
    0xca, 0xd6, 0xac, 0x4f, 0x9f, 0x2d, 0x95, 0x93, 0xc9, 0xc1, 0x59, 0xa9,
    0xa4, 0x55, 0x83, 0x84, 0x01,
};

/* https://github.com/tuupola/drip-scripts/tree/testing/testing */
/* hda16376-16376A.eds with SAM type 0x01 prepended */
static const uint8_t hda16376_16376a[] = {
    0x01, 0x80, 0x0b, 0x2b, 0x0d, 0x00, 0x21, 0xec, 0x10, 0x20, 0x01, 0x00,
    0x3f, 0xfe, 0x3f, 0xf8, 0x05, 0x03, 0x25, 0xd3, 0x4f, 0x5a, 0x5a, 0xd1,
    0x86, 0x50, 0xa2, 0x5e, 0xd5, 0x44, 0xeb, 0x61, 0x72, 0xc8, 0xd1, 0x30,
    0x41, 0x7b, 0xe7, 0x71, 0x7d, 0x8b, 0x77, 0xea, 0x83, 0x9c, 0xd4, 0x2f,
    0x4a, 0xf8, 0x27, 0xfd, 0xa5, 0xbe, 0x84, 0x6c, 0x2a, 0x20, 0x01, 0x00,
    0x3f, 0xfe, 0x00, 0x00, 0x05, 0x4f, 0xb8, 0x7c, 0x27, 0x28, 0x10, 0x70,
    0x48, 0x64, 0xd2, 0xbe, 0xf5, 0x49, 0x19, 0xc6, 0x68, 0xc8, 0xba, 0x95,
    0x79, 0x32, 0x71, 0x52, 0xc7, 0xb7, 0x94, 0x7b, 0x21, 0xee, 0xa4, 0x96,
    0x70, 0xde, 0x5d, 0x1a, 0x8f, 0xb1, 0x07, 0x00, 0x01, 0x18, 0x9c, 0x66,
    0x01, 0x76, 0xd1, 0x13, 0x34, 0xc0, 0xce, 0x15, 0xaf, 0x6b, 0x5f, 0x62,
    0x19, 0xd9, 0x62, 0xad, 0xea, 0x38, 0x0c, 0xf5, 0xe2, 0x5f, 0x26, 0x35,
    0x75, 0xd0, 0xf6, 0x5e, 0x0e,
};
/* clang-format on */

static int det_cshake128_cb(
    void *context, const uint8_t *input, size_t input_length, uint8_t *buffer,
    size_t buffer_size, size_t *output_length
) {
    (void)context;
    int rc = cSHAKE128(
        input, input_length * 8, buffer, buffer_size * 8, NULL, 0, DRIP_DET_CONTEXT_ID,
        sizeof(DRIP_DET_CONTEXT_ID) * 8
    );
    if (rc != 0) {
        return rc;
    }

    *output_length = buffer_size;
    return 0;
}

TEST test_init_null_ptr(void) {
    int rc = drip_link_init(NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_init(void) {
    drip_link_t link;

    int rc = drip_link_init(&link);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_EQ(DRIP_SAM_TYPE_LINK, link.sam_type);
    PASS();
}

TEST test_set_vnb_unixtime_null_ptr(void) {
    int rc = drip_link_set_vnb_unixtime(NULL, 1546300822);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_get_vnb_null_ptr(void) {
    uint32_t result = drip_link_get_vnb(NULL);
    ASSERT_EQ(0, result);
    PASS();
}

TEST test_set_vnb_null_ptr(void) {
    int rc = drip_link_set_vnb(NULL, 123);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_and_get_vnb(void) {
    drip_link_t link;
    uint32_t value = 123456789;

    drip_link_init(&link);
    int rc = drip_link_set_vnb(&link, value);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_EQ(value, drip_link_get_vnb(&link));
    PASS();
}

TEST test_set_vnb_out_of_range(void) {
    drip_link_t link;
    drip_link_init(&link);

    int rc = drip_link_set_vnb(&link, UINT32_MAX);
    ASSERT_EQ(DRIP_ERROR_OUT_OF_RANGE, rc);
    ASSERT_EQ(0, drip_link_get_vnb(&link));
    PASS();
}

TEST test_set_vnb_at_upper_bound(void) {
    drip_link_t link;
    drip_link_init(&link);

    int rc = drip_link_set_vnb(&link, UINT32_MAX - DRIP_TIMESTAMP_EPOCH);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_EQ(UINT32_MAX, drip_link_get_vnb_unixtime(&link));
    PASS();
}

TEST test_get_vna_null_ptr(void) {
    uint32_t result = drip_link_get_vna(NULL);
    ASSERT_EQ(0, result);
    PASS();
}

TEST test_set_vna_null_ptr(void) {
    int rc = drip_link_set_vna(NULL, 123);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_and_get_vna(void) {
    drip_link_t link;
    uint32_t value = 987654321;

    drip_link_init(&link);
    int rc = drip_link_set_vna(&link, value);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_EQ(value, drip_link_get_vna(&link));
    PASS();
}

TEST test_set_vna_out_of_range(void) {
    drip_link_t link;
    drip_link_init(&link);

    int rc = drip_link_set_vna(&link, UINT32_MAX);
    ASSERT_EQ(DRIP_ERROR_OUT_OF_RANGE, rc);
    ASSERT_EQ(0, drip_link_get_vna(&link));
    PASS();
}

TEST test_get_vnb_unixtime_null_ptr(void) {
    uint32_t result = drip_link_get_vnb_unixtime(NULL);
    ASSERT_EQ(0, result);
    PASS();
}

TEST test_set_and_get_vnb_unixtime(void) {
    drip_link_t link;
    uint32_t unixtime = 1546300822;

    drip_link_init(&link);
    int rc = drip_link_set_vnb_unixtime(&link, unixtime);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_EQ(unixtime, drip_link_get_vnb_unixtime(&link));
    PASS();
}

TEST test_set_vna_unixtime_null_ptr(void) {
    int rc = drip_link_set_vna_unixtime(NULL, 1546300822);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_get_vna_unixtime_null_ptr(void) {
    uint32_t result = drip_link_get_vna_unixtime(NULL);
    ASSERT_EQ(0, result);
    PASS();
}

TEST test_set_vnb_unixtime_before_epoch(void) {
    drip_link_t link;
    drip_link_init(&link);

    int rc = drip_link_set_vnb_unixtime(&link, 1546300799);
    ASSERT_EQ(DRIP_ERROR_OUT_OF_RANGE, rc);
    PASS();
}

TEST test_set_vna_unixtime_before_epoch(void) {
    drip_link_t link;
    drip_link_init(&link);

    int rc = drip_link_set_vna_unixtime(&link, 1546300799);
    ASSERT_EQ(DRIP_ERROR_OUT_OF_RANGE, rc);
    PASS();
}

TEST test_set_and_get_vna_unixtime(void) {
    drip_link_t link;
    uint32_t unixtime = 1546300822;

    drip_link_init(&link);
    int rc = drip_link_set_vna_unixtime(&link, unixtime);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_EQ(unixtime, drip_link_get_vna_unixtime(&link));
    PASS();
}

TEST test_get_child_det_null_ptr(void) {
    const drip_det_t *result = drip_link_get_child_det(NULL);
    ASSERT_EQ(NULL, result);
    PASS();
}

TEST test_set_child_det_null_ptr_link(void) {
    drip_det_t det;
    memset(&det, 0x11, sizeof(det));
    int rc = drip_link_set_child_det(NULL, &det);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_child_det_null_ptr_det(void) {
    drip_link_t link;
    drip_link_init(&link);
    int rc = drip_link_set_child_det(&link, NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_and_get_child_det(void) {
    drip_link_t link;
    drip_det_t det;
    memset(&det, 0x11, sizeof(det));

    drip_link_init(&link);
    int rc = drip_link_set_child_det(&link, &det);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    const drip_det_t *result = drip_link_get_child_det(&link);
    ASSERT_NEQ(NULL, result);
    ASSERT_MEM_EQ(det, *result, sizeof(drip_det_t));
    PASS();
}

TEST test_get_child_hi_null_ptr(void) {
    const drip_hi_t *result = drip_link_get_child_hi(NULL);
    ASSERT_EQ(NULL, result);
    PASS();
}

TEST test_set_child_hi_null_ptr_link(void) {
    drip_hi_t hi;
    memset(&hi, 0x11, sizeof(hi));
    int rc = drip_link_set_child_hi(NULL, &hi);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_child_hi_null_ptr_hi(void) {
    drip_link_t link;
    drip_link_init(&link);
    int rc = drip_link_set_child_hi(&link, NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_and_get_child_hi(void) {
    drip_link_t link;
    drip_hi_t hi;
    memset(&hi, 0x11, sizeof(hi));

    drip_link_init(&link);
    int rc = drip_link_set_child_hi(&link, &hi);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    const drip_hi_t *result = drip_link_get_child_hi(&link);
    ASSERT_NEQ(NULL, result);
    ASSERT_MEM_EQ(hi, *result, sizeof(drip_hi_t));
    PASS();
}

TEST test_get_parent_det_null_ptr(void) {
    const drip_det_t *result = drip_link_get_parent_det(NULL);
    ASSERT_EQ(NULL, result);
    PASS();
}

TEST test_set_parent_det_null_ptr_link(void) {
    drip_det_t det;
    memset(&det, 0x11, sizeof(det));
    int rc = drip_link_set_parent_det(NULL, &det);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_parent_det_null_ptr_det(void) {
    drip_link_t link;
    drip_link_init(&link);
    int rc = drip_link_set_parent_det(&link, NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_and_get_parent_det(void) {
    drip_link_t link;
    drip_det_t det;
    memset(&det, 0x11, sizeof(det));

    drip_link_init(&link);
    int rc = drip_link_set_parent_det(&link, &det);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    const drip_det_t *result = drip_link_get_parent_det(&link);
    ASSERT_NEQ(NULL, result);
    ASSERT_MEM_EQ(det, *result, sizeof(drip_det_t));
    PASS();
}

TEST test_get_signature_null_ptr(void) {
    const drip_signature_t *signature = drip_link_get_signature(NULL);
    ASSERT_EQ(NULL, signature);
    PASS();
}

TEST test_set_signature_null_ptr_link(void) {
    drip_signature_t signature;
    memset(&signature, 0x33, sizeof(signature));
    int rc = drip_link_set_signature(NULL, &signature);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_signature_null_ptr_signature(void) {
    drip_link_t link;
    drip_link_init(&link);
    int rc = drip_link_set_signature(&link, NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_and_get_signature(void) {
    drip_link_t link;
    drip_signature_t signature;
    memset(&signature, 0x33, sizeof(signature));

    drip_link_init(&link);
    int rc = drip_link_set_signature(&link, &signature);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    const drip_signature_t *result = drip_link_get_signature(&link);
    ASSERT_NEQ(NULL, result);
    ASSERT_MEM_EQ(signature, *result, sizeof(drip_signature_t));
    PASS();
}

TEST test_decode_null_ptr_link(void) {
    uint8_t buffer[DRIP_LINK_SIZE] = {0};
    int rc = drip_link_decode(NULL, buffer, sizeof(buffer));
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_decode_null_ptr_buffer(void) {
    drip_link_t link;
    drip_link_init(&link);
    int rc = drip_link_decode(&link, NULL, DRIP_LINK_SIZE);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_decode_buffer_too_small(void) {
    drip_link_t link;
    uint8_t buffer[10] = {0};
    int rc = drip_link_decode(&link, buffer, sizeof(buffer));
    ASSERT_EQ(DRIP_ERROR_BUFFER_TOO_SMALL, rc);
    PASS();
}

TEST test_decode_invalid_sam_type(void) {
    drip_link_t link;
    uint8_t buffer[DRIP_LINK_SIZE] = {0};
    buffer[0] = DRIP_SAM_TYPE_WRAPPER;
    int rc = drip_link_decode(&link, buffer, sizeof(buffer));
    ASSERT_EQ(DRIP_ERROR_INVALID_SAM_TYPE, rc);
    PASS();
}

TEST test_decode_success(void) {
    drip_link_t in, out;
    drip_det_t child_det;
    drip_hi_t child_hi;
    drip_det_t parent_det;
    drip_signature_t signature;

    memset(&child_det, 0x11, sizeof(child_det));
    memset(&child_hi, 0x22, sizeof(child_hi));
    memset(&parent_det, 0x33, sizeof(parent_det));
    memset(&signature, 0x44, sizeof(signature));

    drip_link_init(&in);
    drip_link_set_vnb(&in, 100000000);
    drip_link_set_vna(&in, 100000120);
    drip_link_set_child_det(&in, &child_det);
    drip_link_set_child_hi(&in, &child_hi);
    drip_link_set_parent_det(&in, &parent_det);
    drip_link_set_signature(&in, &signature);

    uint8_t buffer[DRIP_LINK_SIZE];
    size_t encoded_length = 0;
    int rc = drip_link_encode(&in, buffer, sizeof(buffer), &encoded_length);
    ASSERT_EQ(DRIP_SUCCESS, rc);

    rc = drip_link_decode(&out, buffer, encoded_length);
    ASSERT_EQ(DRIP_SUCCESS, rc);

    ASSERT_EQ(DRIP_SAM_TYPE_LINK, out.sam_type);
    ASSERT_EQ(100000000, out.vnb);
    ASSERT_EQ(100000120, out.vna);
    ASSERT_MEM_EQ(child_det, out.child_det, sizeof(drip_det_t));
    ASSERT_MEM_EQ(child_hi, out.child_hi, sizeof(drip_hi_t));
    ASSERT_MEM_EQ(parent_det, out.parent_det, sizeof(drip_det_t));
    ASSERT_MEM_EQ(signature, out.signature, sizeof(drip_signature_t));
    PASS();
}

TEST test_encode_null_ptr_link(void) {
    uint8_t buffer[DRIP_LINK_SIZE];
    size_t encoded_length = 0;
    int rc = drip_link_encode(NULL, buffer, sizeof(buffer), &encoded_length);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_encode_null_ptr_buffer(void) {
    drip_link_t link;
    size_t encoded_length = 0;
    drip_link_init(&link);
    int rc = drip_link_encode(&link, NULL, DRIP_LINK_SIZE, &encoded_length);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_encode_null_ptr_encoded_length(void) {
    drip_link_t link;
    uint8_t buffer[DRIP_LINK_SIZE];
    drip_link_init(&link);
    int rc = drip_link_encode(&link, buffer, sizeof(buffer), NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_encode_buffer_too_small(void) {
    drip_link_t link;
    uint8_t buffer[10];
    size_t encoded_length = 0;
    drip_link_init(&link);
    int rc = drip_link_encode(&link, buffer, sizeof(buffer), &encoded_length);
    ASSERT_EQ(DRIP_ERROR_BUFFER_TOO_SMALL, rc);
    PASS();
}

TEST test_encode_success(void) {
    drip_link_t link;
    drip_det_t child_det;
    drip_hi_t child_hi;
    drip_det_t parent_det;
    drip_signature_t signature;

    memset(&child_det, 0x11, sizeof(child_det));
    memset(&child_hi, 0x22, sizeof(child_hi));
    memset(&parent_det, 0x33, sizeof(parent_det));
    memset(&signature, 0x44, sizeof(signature));

    drip_link_init(&link);
    drip_link_set_vnb(&link, 100000000);
    drip_link_set_vna(&link, 100000120);
    drip_link_set_child_det(&link, &child_det);
    drip_link_set_child_hi(&link, &child_hi);
    drip_link_set_parent_det(&link, &parent_det);
    drip_link_set_signature(&link, &signature);

    uint8_t buffer[DRIP_LINK_SIZE];
    size_t encoded_length = 0;
    int rc = drip_link_encode(&link, buffer, sizeof(buffer), &encoded_length);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_EQ(DRIP_LINK_SIZE, encoded_length);
    PASS();
}

TEST test_sign_null_ptr_link(void) {
    int rc = drip_link_sign(NULL, sign_ed25519, (void *)secret_key);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_sign_null_ptr_callback(void) {
    drip_link_t link;
    drip_link_init(&link);
    int rc = drip_link_sign(&link, NULL, (void *)secret_key);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_sign_and_verify_success(void) {
    drip_link_t link;
    drip_det_t child_det;
    drip_hi_t child_hi;
    drip_det_t parent_det;

    memset(&child_det, 0x11, sizeof(child_det));
    memset(&child_hi, 0x22, sizeof(child_hi));
    memset(&parent_det, 0x33, sizeof(parent_det));

    drip_link_init(&link);
    drip_link_set_vnb(&link, 100000000);
    drip_link_set_vna(&link, 100000120);
    drip_link_set_child_det(&link, &child_det);
    drip_link_set_child_hi(&link, &child_hi);
    drip_link_set_parent_det(&link, &parent_det);

    int rc = drip_link_sign(&link, sign_ed25519, (void *)secret_key);
    ASSERT_EQ(DRIP_SUCCESS, rc);

    rc = drip_link_verify(&link, verify_ed25519, (void *)public_key);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    PASS();
}

static int sign_ed25519_wrong_length(
    void *context, const uint8_t *input, size_t input_length, uint8_t *buffer,
    size_t buffer_size, size_t *output_length
) {
    (void)context;
    (void)input;
    (void)input_length;
    (void)buffer;
    (void)buffer_size;
    *output_length = 32;
    return 0;
}

TEST test_sign_invalid_output_length(void) {
    drip_link_t link;
    drip_det_t child_det;
    drip_hi_t child_hi;
    drip_det_t parent_det;

    memset(&child_det, 0x11, sizeof(child_det));
    memset(&child_hi, 0x22, sizeof(child_hi));
    memset(&parent_det, 0x33, sizeof(parent_det));

    drip_link_init(&link);
    drip_link_set_vnb(&link, 100000000);
    drip_link_set_vna(&link, 100000120);
    drip_link_set_child_det(&link, &child_det);
    drip_link_set_child_hi(&link, &child_hi);
    drip_link_set_parent_det(&link, &parent_det);

    int rc = drip_link_sign(&link, sign_ed25519_wrong_length, (void *)secret_key);
    ASSERT_EQ(DRIP_ERROR_INVALID_LENGTH, rc);
    PASS();
}

TEST test_validate_null_pointer(void) {
    int rc = drip_link_validate(NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_validate_invalid_sam_type(void) {
    drip_link_t link;
    drip_det_t child_det;
    drip_det_t parent_det;

    drip_det_init(&child_det);
    drip_det_init(&parent_det);

    drip_link_init(&link);
    drip_link_set_vnb(&link, 50);
    drip_link_set_vna(&link, 100);
    drip_link_set_child_det(&link, &child_det);
    drip_link_set_parent_det(&link, &parent_det);
    link.sam_type = DRIP_SAM_TYPE_WRAPPER;

    int rc = drip_link_validate(&link);
    ASSERT_EQ(DRIP_ERROR_INVALID_SAM_TYPE, rc);
    PASS();
}

TEST test_validate_vnb_gt_vna(void) {
    drip_link_t link;
    drip_det_t child_det;
    drip_det_t parent_det;

    drip_det_init(&child_det);
    drip_det_init(&parent_det);

    drip_link_init(&link);
    drip_link_set_child_det(&link, &child_det);
    drip_link_set_parent_det(&link, &parent_det);
    drip_link_set_vnb(&link, 200);
    drip_link_set_vna(&link, 100);

    int rc = drip_link_validate(&link);
    ASSERT_EQ(DRIP_ERROR_INVALID_TIMESTAMP, rc);
    PASS();
}

TEST test_validate_vnb_eq_vna(void) {
    drip_link_t link;
    drip_det_t child_det;
    drip_det_t parent_det;

    drip_det_init(&child_det);
    drip_det_set_raa(&child_det, 10);
    drip_det_set_hhsi(&child_det, DRIP_HHSI_EDDSA_CSHAKE128);
    drip_det_init(&parent_det);
    drip_det_set_raa(&parent_det, 10);
    drip_det_set_hhsi(&parent_det, DRIP_HHSI_EDDSA_CSHAKE128);

    drip_link_init(&link);
    drip_link_set_child_det(&link, &child_det);
    drip_link_set_parent_det(&link, &parent_det);
    drip_link_set_vnb(&link, 100);
    drip_link_set_vna(&link, 100);

    int rc = drip_link_validate(&link);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    PASS();
}

TEST test_validate_invalid_child_det(void) {
    drip_link_t link;
    drip_det_t parent_det;

    drip_det_init(&parent_det);

    drip_link_init(&link);
    drip_link_set_vnb(&link, 50);
    drip_link_set_vna(&link, 100);
    link.child_det[0] = 0xFF;
    drip_link_set_parent_det(&link, &parent_det);

    int rc = drip_link_validate(&link);
    ASSERT_EQ(DRIP_ERROR_INVALID_CHILD_DET, rc);
    PASS();
}

TEST test_validate_invalid_parent_det(void) {
    drip_link_t link;
    drip_det_t child_det;

    drip_det_init(&child_det);
    drip_det_set_raa(&child_det, 10);
    drip_det_set_hhsi(&child_det, DRIP_HHSI_EDDSA_CSHAKE128);

    drip_link_init(&link);
    drip_link_set_vnb(&link, 50);
    drip_link_set_vna(&link, 100);
    drip_link_set_child_det(&link, &child_det);
    link.parent_det[0] = 0xFF;

    int rc = drip_link_validate(&link);
    ASSERT_EQ(DRIP_ERROR_INVALID_PARENT_DET, rc);
    PASS();
}

TEST test_validate_success(void) {
    drip_link_t link;
    drip_det_t child_det;
    drip_det_t parent_det;

    drip_det_init(&child_det);
    drip_det_set_raa(&child_det, 10);
    drip_det_set_hhsi(&child_det, DRIP_HHSI_EDDSA_CSHAKE128);
    drip_det_init(&parent_det);
    drip_det_set_raa(&parent_det, 10);
    drip_det_set_hhsi(&parent_det, DRIP_HHSI_EDDSA_CSHAKE128);

    drip_link_init(&link);
    drip_link_set_vnb(&link, 50);
    drip_link_set_vna(&link, 100);
    drip_link_set_child_det(&link, &child_det);
    drip_link_set_parent_det(&link, &parent_det);

    int rc = drip_link_validate(&link);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    PASS();
}

TEST test_to_json_null_ptr_link(void) {
    char buffer[256];
    size_t json_length = 0;
    int rc = drip_link_to_json(NULL, buffer, sizeof(buffer), &json_length);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_to_json_null_ptr_buffer(void) {
    drip_link_t link;
    drip_link_init(&link);
    size_t json_length = 0;
    int rc = drip_link_to_json(&link, NULL, 256, &json_length);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_to_json_optional_json_length(void) {
    drip_link_t link;
    drip_link_init(&link);
    char buffer[1024];
    int rc = drip_link_to_json(&link, buffer, sizeof(buffer), NULL);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    PASS();
}

TEST test_verify_chain_null_ptr(void) {
    drip_link_t link;
    drip_det_t root_det;
    drip_hi_t root_hi;
    drip_link_init(&link);

    ASSERT_EQ(
        DRIP_ERROR_NULL_POINTER,
        drip_link_verify_chain(
            NULL, 1, &root_det, &root_hi, 0, dummy_hash_cb, dummy_verify_cb
        )
    );
    ASSERT_EQ(
        DRIP_ERROR_NULL_POINTER,
        drip_link_verify_chain(
            &link, 1, NULL, &root_hi, 0, dummy_hash_cb, dummy_verify_cb
        )
    );
    ASSERT_EQ(
        DRIP_ERROR_NULL_POINTER,
        drip_link_verify_chain(
            &link, 1, &root_det, NULL, 0, dummy_hash_cb, dummy_verify_cb
        )
    );
    ASSERT_EQ(
        DRIP_ERROR_NULL_POINTER,
        drip_link_verify_chain(&link, 1, &root_det, &root_hi, 0, NULL, verify_ed25519)
    );
    ASSERT_EQ(
        DRIP_ERROR_NULL_POINTER,
        drip_link_verify_chain(&link, 1, &root_det, &root_hi, 0, dummy_hash_cb, NULL)
    );
    PASS();
}

TEST test_verify_chain_empty(void) {
    drip_link_t link;
    drip_det_t root_det;
    drip_hi_t root_hi;
    drip_link_init(&link);

    int rc = drip_link_verify_chain(
        &link, 0, &root_det, &root_hi, 0, dummy_hash_cb, dummy_verify_cb
    );
    ASSERT_EQ(DRIP_ERROR_VERIFICATION_FAILED, rc);
    PASS();
}

/* TODO: checks only DET, does not do any crypto. */
TEST test_verify_chain_parent_det_match(void) {
    drip_link_t link;
    drip_det_t root_det;
    drip_hi_t root_hi;

    memset(&root_det, 0x11, sizeof(root_det));
    drip_link_init(&link);
    drip_link_set_parent_det(&link, &root_det);

    int rc = drip_link_verify_chain(
        &link, 1, &root_det, &root_hi, 0, dummy_hash_cb, dummy_verify_cb
    );
    ASSERT_EQ(DRIP_SUCCESS, rc);
    PASS();
}

/* TODO: checks only DET, does not do any crypto. */
TEST test_verify_chain_parent_det_mismatch(void) {
    drip_link_t link;
    drip_det_t root_det, parent_det;
    drip_hi_t root_hi;

    memset(&root_det, 0x11, sizeof(root_det));
    memset(&parent_det, 0x22, sizeof(parent_det));
    drip_link_init(&link);
    drip_link_set_parent_det(&link, &parent_det);

    int rc = drip_link_verify_chain(
        &link, 1, &root_det, &root_hi, 0, dummy_hash_cb, dummy_verify_cb
    );
    ASSERT_EQ(DRIP_ERROR_VERIFICATION_FAILED, rc);
    PASS();
}

/* TODO: checks only DET, does not do any crypto. */
TEST test_verify_chain_two_hop_match(void) {
    drip_link_t links[2];
    drip_det_t root_det, child_det;
    drip_hi_t root_hi;

    memset(&root_det, 0x11, sizeof(root_det));
    memset(&child_det, 0x22, sizeof(child_det));

    drip_link_init(&links[0]);
    drip_link_set_parent_det(&links[0], &root_det);
    drip_link_set_child_det(&links[0], &child_det);

    drip_link_init(&links[1]);
    drip_link_set_parent_det(&links[1], &child_det);

    int rc = drip_link_verify_chain(
        links, 2, &root_det, &root_hi, 0, dummy_hash_cb, dummy_verify_cb
    );
    ASSERT_EQ(DRIP_SUCCESS, rc);
    PASS();
}

/* TODO: checks only DET, does not do any crypto. */
TEST test_verify_chain_two_hop_mismatch(void) {
    drip_link_t links[2];
    drip_det_t root_det, child_det, other_det;
    drip_hi_t root_hi;

    memset(&root_det, 0x11, sizeof(root_det));
    memset(&child_det, 0x22, sizeof(child_det));
    memset(&other_det, 0x33, sizeof(other_det));

    drip_link_init(&links[0]);
    drip_link_set_parent_det(&links[0], &root_det);
    drip_link_set_child_det(&links[0], &child_det);

    drip_link_init(&links[1]);
    drip_link_set_parent_det(&links[1], &other_det);

    int rc = drip_link_verify_chain(
        links, 2, &root_det, &root_hi, 0, dummy_hash_cb, dummy_verify_cb
    );
    ASSERT_EQ(DRIP_ERROR_VERIFICATION_FAILED, rc);
    PASS();
}

TEST test_verify_chain_unixtime_skipped(void) {
    drip_link_t link;
    drip_det_t root_det;
    drip_hi_t root_hi;
    uint32_t now = 1600000000;

    memset(&root_det, 0x11, sizeof(root_det));
    drip_link_init(&link);
    drip_link_set_parent_det(&link, &root_det);
    drip_link_set_vnb_unixtime(&link, now - 20);
    drip_link_set_vna_unixtime(&link, now - 10);

    int rc = drip_link_verify_chain(
        &link, 1, &root_det, &root_hi, 0, dummy_hash_cb, dummy_verify_cb
    );
    ASSERT_EQ(DRIP_SUCCESS, rc);
    PASS();
}

TEST test_verify_chain_unixtime_success(void) {
    drip_link_t link;
    drip_det_t root_det;
    drip_hi_t root_hi;
    uint32_t now = 1600000000;

    memset(&root_det, 0x11, sizeof(root_det));
    drip_link_init(&link);
    drip_link_set_parent_det(&link, &root_det);
    drip_link_set_vnb_unixtime(&link, now - 10);
    drip_link_set_vna_unixtime(&link, now + 10);

    int rc = drip_link_verify_chain(
        &link, 1, &root_det, &root_hi, now, dummy_hash_cb, dummy_verify_cb
    );
    ASSERT_EQ(DRIP_SUCCESS, rc);

    rc = drip_link_verify_chain(
        &link, 1, &root_det, &root_hi, now - 10, dummy_hash_cb, dummy_verify_cb
    );
    ASSERT_EQ(DRIP_SUCCESS, rc);

    rc = drip_link_verify_chain(
        &link, 1, &root_det, &root_hi, now + 10, dummy_hash_cb, dummy_verify_cb
    );
    ASSERT_EQ(DRIP_SUCCESS, rc);
    PASS();
}

TEST test_verify_chain_unixtime_expired(void) {
    drip_link_t link;
    drip_det_t root_det;
    drip_hi_t root_hi;
    uint32_t now = 1600000000;

    memset(&root_det, 0x11, sizeof(root_det));
    drip_link_init(&link);
    drip_link_set_parent_det(&link, &root_det);
    drip_link_set_vnb_unixtime(&link, now - 10);
    drip_link_set_vna_unixtime(&link, now + 10);

    int rc = drip_link_verify_chain(
        &link, 1, &root_det, &root_hi, now - 11, dummy_hash_cb, dummy_verify_cb
    );
    ASSERT_EQ(DRIP_ERROR_INVALID_TIMESTAMP, rc);

    rc = drip_link_verify_chain(
        &link, 1, &root_det, &root_hi, now + 11, dummy_hash_cb, dummy_verify_cb
    );
    ASSERT_EQ(DRIP_ERROR_INVALID_TIMESTAMP, rc);
    PASS();
}

TEST test_verify_chain_two_hop_unixtime_expired(void) {
    drip_link_t links[2];
    drip_det_t root_det, child_det;
    drip_hi_t root_hi;
    uint32_t now = 1600000000;

    memset(&root_det, 0x11, sizeof(root_det));
    memset(&child_det, 0x22, sizeof(child_det));

    drip_link_init(&links[0]);
    drip_link_set_parent_det(&links[0], &root_det);
    drip_link_set_child_det(&links[0], &child_det);
    drip_link_set_vnb_unixtime(&links[0], now - 10);
    drip_link_set_vna_unixtime(&links[0], now + 10);

    drip_link_init(&links[1]);
    drip_link_set_parent_det(&links[1], &child_det);
    drip_link_set_vnb_unixtime(&links[1], now - 30);
    drip_link_set_vna_unixtime(&links[1], now - 20);

    int rc = drip_link_verify_chain(
        links, 2, &root_det, &root_hi, now, dummy_hash_cb, dummy_verify_cb
    );
    ASSERT_EQ(DRIP_ERROR_INVALID_TIMESTAMP, rc);
    PASS();
}

TEST test_verify_chain_child_hash_mismatch(void) {
    drip_link_t link;
    drip_det_t root_det, child_det;
    drip_hi_t root_hi;
    drip_hash_t bad_hash;

    memset(&root_det, 0x11, sizeof(root_det));
    memset(&child_det, 0x11, sizeof(child_det));
    memset(&bad_hash, 0xFF, sizeof(bad_hash));
    drip_det_set_hash(&child_det, &bad_hash);

    drip_link_init(&link);
    drip_link_set_parent_det(&link, &root_det);
    drip_link_set_child_det(&link, &child_det);

    int rc = drip_link_verify_chain(
        &link, 1, &root_det, &root_hi, 0, dummy_hash_cb, dummy_verify_cb
    );
    ASSERT_EQ(DRIP_ERROR_VERIFICATION_FAILED, rc);
    PASS();
}

TEST test_verify_chain_hash_cb_failed(void) {
    drip_link_t link;
    drip_det_t root_det;
    drip_hi_t root_hi;

    memset(&root_det, 0x11, sizeof(root_det));
    drip_link_init(&link);
    drip_link_set_parent_det(&link, &root_det);

    int rc = drip_link_verify_chain(
        &link, 1, &root_det, &root_hi, 0, failing_hash_cb, dummy_verify_cb
    );
    ASSERT_EQ(DRIP_ERROR_CALLBACK_FAILED, rc);
    PASS();
}

TEST test_verify_chain_two_hop_child_hash_mismatch(void) {
    drip_link_t links[2];
    drip_det_t root_det, child_det, leaf_det;
    drip_hi_t root_hi;
    drip_hash_t bad_hash;

    memset(&root_det, 0x11, sizeof(root_det));
    memset(&child_det, 0x22, sizeof(child_det));
    memset(&leaf_det, 0x33, sizeof(leaf_det));
    memset(&bad_hash, 0xFF, sizeof(bad_hash));
    drip_det_set_hash(&leaf_det, &bad_hash);

    drip_link_init(&links[0]);
    drip_link_set_parent_det(&links[0], &root_det);
    drip_link_set_child_det(&links[0], &child_det);

    drip_link_init(&links[1]);
    drip_link_set_parent_det(&links[1], &child_det);
    drip_link_set_child_det(&links[1], &leaf_det);

    int rc = drip_link_verify_chain(
        links, 2, &root_det, &root_hi, 0, dummy_hash_cb, dummy_verify_cb
    );
    ASSERT_EQ(DRIP_ERROR_VERIFICATION_FAILED, rc);
    PASS();
}

TEST test_verify_chain_signature_success(void) {
    drip_link_t link;
    drip_det_t root_det, child_det;
    drip_hi_t root_hi, child_hi;

    memset(&root_det, 0x11, sizeof(root_det));
    memset(&child_det, 0x22, sizeof(child_det));
    memcpy(root_hi, public_key, sizeof(root_hi));
    memset(&child_hi, 0x33, sizeof(child_hi));

    drip_link_init(&link);
    drip_link_set_parent_det(&link, &root_det);
    drip_link_set_child_det(&link, &child_det);
    drip_link_set_child_hi(&link, &child_hi);
    int rc = drip_link_sign(&link, sign_ed25519, (void *)secret_key);
    ASSERT_EQ(DRIP_SUCCESS, rc);

    rc = drip_link_verify_chain(
        &link, 1, &root_det, &root_hi, 0, dummy_hash_cb, verify_ed25519
    );
    ASSERT_EQ(DRIP_SUCCESS, rc);
    PASS();
}

TEST test_verify_chain_signature_failed(void) {
    drip_link_t link;
    drip_det_t root_det, child_det;
    drip_hi_t root_hi, child_hi;

    memset(&root_det, 0x11, sizeof(root_det));
    memset(&child_det, 0x22, sizeof(child_det));
    memcpy(root_hi, public_key, sizeof(root_hi));
    memset(&child_hi, 0x33, sizeof(child_hi));

    drip_link_init(&link);
    drip_link_set_parent_det(&link, &root_det);
    drip_link_set_child_det(&link, &child_det);
    drip_link_set_child_hi(&link, &child_hi);
    int rc = drip_link_sign(&link, sign_ed25519, (void *)secret_key);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    link.signature[0] ^= 0xFF;

    rc = drip_link_verify_chain(
        &link, 1, &root_det, &root_hi, 0, dummy_hash_cb, verify_ed25519
    );
    ASSERT_EQ(DRIP_ERROR_CALLBACK_FAILED, rc);
    PASS();
}

TEST test_verify_chain_wrong_root_hi(void) {
    drip_link_t link;
    drip_det_t root_det, child_det;
    drip_hi_t child_hi, wrong_hi;

    memset(&root_det, 0x11, sizeof(root_det));
    memset(&child_det, 0x22, sizeof(child_det));
    memset(&child_hi, 0x33, sizeof(child_hi));
    memset(&wrong_hi, 0xAA, sizeof(wrong_hi));

    drip_link_init(&link);
    drip_link_set_parent_det(&link, &root_det);
    drip_link_set_child_det(&link, &child_det);
    drip_link_set_child_hi(&link, &child_hi);
    int rc = drip_link_sign(&link, sign_ed25519, (void *)secret_key);
    ASSERT_EQ(DRIP_SUCCESS, rc);

    rc = drip_link_verify_chain(
        &link, 1, &root_det, &wrong_hi, 0, dummy_hash_cb, verify_ed25519
    );
    ASSERT_EQ(DRIP_ERROR_CALLBACK_FAILED, rc);
    PASS();
}

TEST test_verify_chain_two_hop_signature_success(void) {
    drip_link_t links[2];
    drip_det_t root_det, raa_det, ua_det;
    drip_hi_t root_hi, raa_hi, ua_hi;
    uint8_t root_sk[64], raa_sk[64];

    memset(&root_det, 0x11, sizeof(root_det));
    memset(&raa_det, 0x22, sizeof(raa_det));
    memset(&ua_det, 0x33, sizeof(ua_det));
    memset(&ua_hi, 0x44, sizeof(ua_hi));

    crypto_sign_keypair(root_hi, root_sk);
    crypto_sign_keypair(raa_hi, raa_sk);

    drip_link_init(&links[0]);
    drip_link_set_parent_det(&links[0], &root_det);
    drip_link_set_child_det(&links[0], &raa_det);
    drip_link_set_child_hi(&links[0], &raa_hi);
    int rc = drip_link_sign(&links[0], sign_ed25519, (void *)root_sk);
    ASSERT_EQ(DRIP_SUCCESS, rc);

    drip_link_init(&links[1]);
    drip_link_set_parent_det(&links[1], &raa_det);
    drip_link_set_child_det(&links[1], &ua_det);
    drip_link_set_child_hi(&links[1], &ua_hi);
    rc = drip_link_sign(&links[1], sign_ed25519, (void *)raa_sk);
    ASSERT_EQ(DRIP_SUCCESS, rc);

    rc = drip_link_verify_chain(
        links, 2, &root_det, &root_hi, 0, dummy_hash_cb, verify_ed25519
    );
    ASSERT_EQ(DRIP_SUCCESS, rc);
    PASS();
}

TEST test_verify_chain_fixture_full_chain(void) {
    drip_link_t root, links[3];

    ASSERT_EQ(DRIP_SUCCESS, drip_link_decode(&root, raa16376, sizeof(raa16376)));
    ASSERT_EQ(
        DRIP_SUCCESS,
        drip_link_decode(&links[0], hda16376_16376a, sizeof(hda16376_16376a))
    );
    ASSERT_EQ(
        DRIP_SUCCESS,
        drip_link_decode(&links[1], hda16376_16376i, sizeof(hda16376_16376i))
    );
    ASSERT_EQ(
        DRIP_SUCCESS,
        drip_link_decode(&links[2], ua1_16376_16376, sizeof(ua1_16376_16376))
    );

    int rc = drip_link_verify_chain(
        links, 3, drip_link_get_child_det(&root), drip_link_get_child_hi(&root), 0,
        det_cshake128_cb, verify_ed25519
    );
    ASSERT_EQ(DRIP_SUCCESS, rc);
    PASS();
}

SUITE(link_suite) {
    RUN_TEST(test_init_null_ptr);
    RUN_TEST(test_init);
    RUN_TEST(test_get_vnb_null_ptr);
    RUN_TEST(test_set_vnb_null_ptr);
    RUN_TEST(test_set_and_get_vnb);
    RUN_TEST(test_set_vnb_out_of_range);
    RUN_TEST(test_set_vnb_at_upper_bound);
    RUN_TEST(test_get_vna_null_ptr);
    RUN_TEST(test_set_vna_null_ptr);
    RUN_TEST(test_set_and_get_vna);
    RUN_TEST(test_set_vna_out_of_range);
    RUN_TEST(test_set_vnb_unixtime_null_ptr);
    RUN_TEST(test_get_vnb_unixtime_null_ptr);
    RUN_TEST(test_set_and_get_vnb_unixtime);
    RUN_TEST(test_set_vnb_unixtime_before_epoch);
    RUN_TEST(test_set_vna_unixtime_null_ptr);
    RUN_TEST(test_get_vna_unixtime_null_ptr);
    RUN_TEST(test_set_and_get_vna_unixtime);
    RUN_TEST(test_set_vna_unixtime_before_epoch);
    RUN_TEST(test_get_child_det_null_ptr);
    RUN_TEST(test_set_child_det_null_ptr_link);
    RUN_TEST(test_set_child_det_null_ptr_det);
    RUN_TEST(test_set_and_get_child_det);
    RUN_TEST(test_get_child_hi_null_ptr);
    RUN_TEST(test_set_child_hi_null_ptr_link);
    RUN_TEST(test_set_child_hi_null_ptr_hi);
    RUN_TEST(test_set_and_get_child_hi);
    RUN_TEST(test_get_parent_det_null_ptr);
    RUN_TEST(test_set_parent_det_null_ptr_link);
    RUN_TEST(test_set_parent_det_null_ptr_det);
    RUN_TEST(test_set_and_get_parent_det);
    RUN_TEST(test_get_signature_null_ptr);
    RUN_TEST(test_set_signature_null_ptr_link);
    RUN_TEST(test_set_signature_null_ptr_signature);
    RUN_TEST(test_set_and_get_signature);
    RUN_TEST(test_decode_null_ptr_link);
    RUN_TEST(test_decode_null_ptr_buffer);
    RUN_TEST(test_decode_buffer_too_small);
    RUN_TEST(test_decode_invalid_sam_type);
    RUN_TEST(test_decode_success);
    RUN_TEST(test_encode_null_ptr_link);
    RUN_TEST(test_encode_null_ptr_buffer);
    RUN_TEST(test_encode_null_ptr_encoded_length);
    RUN_TEST(test_encode_buffer_too_small);
    RUN_TEST(test_encode_success);
    RUN_TEST(test_sign_null_ptr_link);
    RUN_TEST(test_sign_null_ptr_callback);
    RUN_TEST(test_sign_and_verify_success);
    RUN_TEST(test_sign_invalid_output_length);
    RUN_TEST(test_validate_null_pointer);
    RUN_TEST(test_validate_invalid_sam_type);
    RUN_TEST(test_validate_vnb_gt_vna);
    RUN_TEST(test_validate_vnb_eq_vna);
    RUN_TEST(test_validate_invalid_child_det);
    RUN_TEST(test_validate_invalid_parent_det);
    RUN_TEST(test_validate_success);
    RUN_TEST(test_to_json_null_ptr_link);
    RUN_TEST(test_to_json_null_ptr_buffer);
    RUN_TEST(test_to_json_optional_json_length);
    RUN_TEST(test_verify_chain_null_ptr);
    RUN_TEST(test_verify_chain_empty);
    RUN_TEST(test_verify_chain_parent_det_match);
    RUN_TEST(test_verify_chain_parent_det_mismatch);
    RUN_TEST(test_verify_chain_two_hop_match);
    RUN_TEST(test_verify_chain_two_hop_mismatch);
    RUN_TEST(test_verify_chain_unixtime_skipped);
    RUN_TEST(test_verify_chain_unixtime_success);
    RUN_TEST(test_verify_chain_unixtime_expired);
    RUN_TEST(test_verify_chain_two_hop_unixtime_expired);
    RUN_TEST(test_verify_chain_child_hash_mismatch);
    RUN_TEST(test_verify_chain_hash_cb_failed);
    RUN_TEST(test_verify_chain_two_hop_child_hash_mismatch);
    RUN_TEST(test_verify_chain_signature_success);
    RUN_TEST(test_verify_chain_signature_failed);
    RUN_TEST(test_verify_chain_wrong_root_hi);
    RUN_TEST(test_verify_chain_two_hop_signature_success);
    RUN_TEST(test_verify_chain_fixture_full_chain);
}
