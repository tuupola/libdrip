#include <sodium.h>
#include <stdint.h>
#include <string.h>

#include "drip/format.h"
#include "drip/link.h"
#include "unit.h"

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

static int sign_ed25519(
    void *context,
    const uint8_t *input,
    size_t input_length,
    uint8_t *signature,
    size_t signature_size,
    size_t *signature_length
) {
    (void)signature_size;
    const uint8_t *key = (const uint8_t *)context;
    unsigned long long sig_len = 0;
    int rc = crypto_sign_detached(signature, &sig_len, input, input_length, key);
    if (0 == rc) {
        *signature_length = (size_t)sig_len;
    }
    return rc;
}

static int verify_ed25519(
    void *context, const uint8_t *message, size_t message_len,
    const uint8_t *signature, size_t signature_length
) {
    (void)signature_length;
    const uint8_t *key = (const uint8_t *)context;
    return crypto_sign_verify_detached(signature, message, message_len, key);
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
    const drip_signature_t *sig = drip_link_get_signature(NULL);
    ASSERT_EQ(NULL, sig);
    PASS();
}

TEST test_set_signature_null_ptr_link(void) {
    drip_signature_t sig;
    memset(&sig, 0x33, sizeof(sig));
    int rc = drip_link_set_signature(NULL, &sig);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_signature_null_ptr_sig(void) {
    drip_link_t link;
    drip_link_init(&link);
    int rc = drip_link_set_signature(&link, NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_and_get_signature(void) {
    drip_link_t link;
    drip_signature_t sig;
    memset(&sig, 0x33, sizeof(sig));

    drip_link_init(&link);
    int rc = drip_link_set_signature(&link, &sig);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    const drip_signature_t *result = drip_link_get_signature(&link);
    ASSERT_NEQ(NULL, result);
    ASSERT_MEM_EQ(sig, *result, sizeof(drip_signature_t));
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

TEST test_decode_buffer_too_large(void) {
    drip_link_t link;
    uint8_t buffer[256] = {0};
    int rc = drip_link_decode(&link, buffer, sizeof(buffer));
    ASSERT_EQ(DRIP_ERROR_BUFFER_TOO_LARGE, rc);
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
    drip_signature_t sig;

    memset(&child_det, 0x11, sizeof(child_det));
    memset(&child_hi, 0x22, sizeof(child_hi));
    memset(&parent_det, 0x33, sizeof(parent_det));
    memset(&sig, 0x44, sizeof(sig));

    drip_link_init(&in);
    drip_link_set_vnb(&in, 100000000);
    drip_link_set_vna(&in, 100000120);
    drip_link_set_child_det(&in, &child_det);
    drip_link_set_child_hi(&in, &child_hi);
    drip_link_set_parent_det(&in, &parent_det);
    drip_link_set_signature(&in, &sig);

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
    ASSERT_MEM_EQ(sig, out.signature, sizeof(drip_signature_t));
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
    drip_signature_t sig;

    memset(&child_det, 0x11, sizeof(child_det));
    memset(&child_hi, 0x22, sizeof(child_hi));
    memset(&parent_det, 0x33, sizeof(parent_det));
    memset(&sig, 0x44, sizeof(sig));

    drip_link_init(&link);
    drip_link_set_vnb(&link, 100000000);
    drip_link_set_vna(&link, 100000120);
    drip_link_set_child_det(&link, &child_det);
    drip_link_set_child_hi(&link, &child_hi);
    drip_link_set_parent_det(&link, &parent_det);
    drip_link_set_signature(&link, &sig);

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
    void *context,
    const uint8_t *input,
    size_t input_length,
    uint8_t *signature,
    size_t signature_size,
    size_t *signature_length
) {
    (void)context;
    (void)input;
    (void)input_length;
    (void)signature;
    (void)signature_size;
    *signature_length = 32;
    return 0;
}

TEST test_sign_invalid_signature_length(void) {
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

SUITE(link_suite) {
    RUN_TEST(test_init_null_ptr);
    RUN_TEST(test_init);
    RUN_TEST(test_get_vnb_null_ptr);
    RUN_TEST(test_set_vnb_null_ptr);
    RUN_TEST(test_set_and_get_vnb);
    RUN_TEST(test_get_vna_null_ptr);
    RUN_TEST(test_set_vna_null_ptr);
    RUN_TEST(test_set_and_get_vna);
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
    RUN_TEST(test_set_signature_null_ptr_sig);
    RUN_TEST(test_set_and_get_signature);
    RUN_TEST(test_decode_null_ptr_link);
    RUN_TEST(test_decode_null_ptr_buffer);
    RUN_TEST(test_decode_buffer_too_small);
    RUN_TEST(test_decode_buffer_too_large);
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
    RUN_TEST(test_sign_invalid_signature_length);
}
