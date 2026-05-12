#include <stdint.h>
#include <string.h>

#include "drip/manifest.h"
#include "unit.h"

TEST test_init_null_pointer(void) {
    int rc = drip_manifest_init(NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_init(void) {
    drip_manifest_t message;

    int rc = drip_manifest_init(&message);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_EQ(DRIP_SAM_TYPE_MANIFEST, message.sam_type);
    PASS();
}

TEST test_get_vnb_null_ptr(void) {
    uint32_t result = drip_manifest_get_vnb(NULL);
    ASSERT_EQ(0, result);
    PASS();
}

TEST test_set_vnb_null_ptr(void) {
    int rc = drip_manifest_set_vnb(NULL, 123);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_and_get_vnb(void) {
    drip_manifest_t message;
    uint32_t value = 123456789;

    drip_manifest_init(&message);
    int rc = drip_manifest_set_vnb(&message, value);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_EQ(value, drip_manifest_get_vnb(&message));
    PASS();
}

TEST test_get_vna_null_ptr(void) {
    uint32_t result = drip_manifest_get_vna(NULL);
    ASSERT_EQ(0, result);
    PASS();
}

TEST test_set_vna_null_ptr(void) {
    int rc = drip_manifest_set_vna(NULL, 123);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_and_get_vna(void) {
    drip_manifest_t message;
    uint32_t value = 987654321;

    drip_manifest_init(&message);
    int rc = drip_manifest_set_vna(&message, value);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_EQ(value, drip_manifest_get_vna(&message));
    PASS();
}

TEST test_get_previous_manifest_hash_null_ptr_manifest(void) {
    drip_hash_t hash = {0};
    int rc = drip_manifest_get_previous_manifest_hash(NULL, &hash);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_get_previous_manifest_hash_null_ptr_hash(void) {
    drip_manifest_t message;
    drip_manifest_init(&message);
    int rc = drip_manifest_get_previous_manifest_hash(&message, NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_previous_manifest_hash_null_ptr_manifest(void) {
    drip_hash_t hash = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    int rc = drip_manifest_set_previous_manifest_hash(NULL, &hash);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_previous_manifest_hash_null_ptr_hash(void) {
    drip_manifest_t message;
    drip_manifest_init(&message);
    int rc = drip_manifest_set_previous_manifest_hash(&message, NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_and_get_previous_manifest_hash(void) {
    drip_manifest_t message;
    drip_hash_t hash = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    drip_hash_t result;

    drip_manifest_init(&message);
    int rc = drip_manifest_set_previous_manifest_hash(&message, hash);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    rc = drip_manifest_get_previous_manifest_hash(&message, result);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_MEM_EQ(hash, result, sizeof(drip_hash_t));
    PASS();
}

TEST test_get_current_manifest_hash_null_ptr_manifest(void) {
    drip_hash_t hash = {0};
    int rc = drip_manifest_get_current_manifest_hash(NULL, &hash);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_get_current_manifest_hash_null_ptr_hash(void) {
    drip_manifest_t message;
    drip_manifest_init(&message);
    int rc = drip_manifest_get_current_manifest_hash(&message, NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_current_manifest_hash_null_ptr_manifest(void) {
    drip_hash_t hash = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
    int rc = drip_manifest_set_current_manifest_hash(NULL, &hash);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_current_manifest_hash_null_ptr_hash(void) {
    drip_manifest_t message;
    drip_manifest_init(&message);
    int rc = drip_manifest_set_current_manifest_hash(&message, NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_and_get_current_manifest_hash(void) {
    drip_manifest_t message;
    drip_hash_t hash = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
    drip_hash_t result;

    drip_manifest_init(&message);
    int rc = drip_manifest_set_current_manifest_hash(&message, hash);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    rc = drip_manifest_get_current_manifest_hash(&message, result);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_MEM_EQ(hash, result, sizeof(drip_hash_t));
    PASS();
}

TEST test_get_drip_link_hash_null_ptr_manifest(void) {
    drip_hash_t hash = {0};
    int rc = drip_manifest_get_drip_link_hash(NULL, &hash);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_get_drip_link_hash_null_ptr_hash(void) {
    drip_manifest_t message;
    drip_manifest_init(&message);
    int rc = drip_manifest_get_drip_link_hash(&message, NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_drip_link_hash_null_ptr_manifest(void) {
    drip_hash_t hash = {0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28};
    int rc = drip_manifest_set_drip_link_hash(NULL, &hash);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_drip_link_hash_null_ptr_hash(void) {
    drip_manifest_t message;
    drip_manifest_init(&message);
    int rc = drip_manifest_set_drip_link_hash(&message, NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_and_get_drip_link_hash(void) {
    drip_manifest_t message;
    drip_hash_t hash = {0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28};
    drip_hash_t result;

    drip_manifest_init(&message);
    int rc = drip_manifest_set_drip_link_hash(&message, hash);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    rc = drip_manifest_get_drip_link_hash(&message, result);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_MEM_EQ(hash, result, sizeof(drip_hash_t));
    PASS();
}

TEST test_get_det_null_ptr_manifest(void) {
    drip_det_t det = {0};
    int rc = drip_manifest_get_det(NULL, &det);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_get_det_null_ptr_det(void) {
    drip_manifest_t message;
    drip_manifest_init(&message);
    int rc = drip_manifest_get_det(&message, NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_det_null_ptr_manifest(void) {
    drip_det_t det = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40};
    int rc = drip_manifest_set_det(NULL, &det);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_det_null_ptr_det(void) {
    drip_manifest_t message;
    drip_manifest_init(&message);
    int rc = drip_manifest_set_det(&message, NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_and_get_det(void) {
    drip_manifest_t message;
    drip_det_t det = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40};
    drip_det_t result;

    drip_manifest_init(&message);
    int rc = drip_manifest_set_det(&message, det);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    rc = drip_manifest_get_det(&message, result);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_MEM_EQ(det, result, sizeof(drip_det_t));
    PASS();
}

TEST test_get_signature_null_ptr_manifest(void) {
    drip_sig_t sig = {0};
    int rc = drip_manifest_get_signature(NULL, &sig);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_get_signature_null_ptr_sig(void) {
    drip_manifest_t message;
    drip_manifest_init(&message);
    int rc = drip_manifest_get_signature(&message, NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_signature_null_ptr_manifest(void) {
    drip_sig_t sig = {0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90};
    int rc = drip_manifest_set_signature(NULL, &sig);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_signature_null_ptr_sig(void) {
    drip_manifest_t message;
    drip_manifest_init(&message);
    int rc = drip_manifest_set_signature(&message, NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_and_get_signature(void) {
    drip_manifest_t message;
    drip_sig_t sig = {0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90};
    drip_sig_t result;

    drip_manifest_init(&message);
    int rc = drip_manifest_set_signature(&message, sig);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    rc = drip_manifest_get_signature(&message, result);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_MEM_EQ(sig, result, sizeof(drip_sig_t));
    PASS();
}

TEST test_add_message_hash_null_ptr_manifest(void) {
    drip_hash_t hash = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    int rc = drip_manifest_add_message_hash(NULL, &hash);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_add_message_hash_null_ptr_hash(void) {
    drip_manifest_t message;
    drip_manifest_init(&message);
    int rc = drip_manifest_add_message_hash(&message, NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_add_message_hash_array_full(void) {
    drip_manifest_t message;
    drip_hash_t hash = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    int rc;

    drip_manifest_init(&message);
    for (int i = 0; i < DRIP_MANIFEST_MESSAGE_MAX; i++) {
        rc = drip_manifest_add_message_hash(&message, &hash);
        ASSERT_EQ(DRIP_SUCCESS, rc);
    }
    rc = drip_manifest_add_message_hash(&message, &hash);
    ASSERT_EQ(DRIP_ERROR_ARRAY_FULL, rc);
    PASS();
}

TEST test_add_message_hash_success(void) {
    drip_manifest_t message;
    drip_hash_t hash1 = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    drip_hash_t hash2 = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};

    drip_manifest_init(&message);
    int rc = drip_manifest_add_message_hash(&message, &hash1);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_EQ(1, message.message_hash_count);
    ASSERT_MEM_EQ(hash1, message.message_hash_array[0], sizeof(drip_hash_t));

    rc = drip_manifest_add_message_hash(&message, &hash2);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_EQ(2, message.message_hash_count);
    ASSERT_MEM_EQ(hash2, message.message_hash_array[1], sizeof(drip_hash_t));
    PASS();
}

SUITE(manifest_suite) {
    RUN_TEST(test_init_null_pointer);
    RUN_TEST(test_init);
    RUN_TEST(test_get_vnb_null_ptr);
    RUN_TEST(test_set_vnb_null_ptr);
    RUN_TEST(test_set_and_get_vnb);
    RUN_TEST(test_get_vna_null_ptr);
    RUN_TEST(test_set_vna_null_ptr);
    RUN_TEST(test_set_and_get_vna);
    RUN_TEST(test_get_previous_manifest_hash_null_ptr_manifest);
    RUN_TEST(test_get_previous_manifest_hash_null_ptr_hash);
    RUN_TEST(test_set_previous_manifest_hash_null_ptr_manifest);
    RUN_TEST(test_set_previous_manifest_hash_null_ptr_hash);
    RUN_TEST(test_set_and_get_previous_manifest_hash);
    RUN_TEST(test_get_current_manifest_hash_null_ptr_manifest);
    RUN_TEST(test_get_current_manifest_hash_null_ptr_hash);
    RUN_TEST(test_set_current_manifest_hash_null_ptr_manifest);
    RUN_TEST(test_set_current_manifest_hash_null_ptr_hash);
    RUN_TEST(test_set_and_get_current_manifest_hash);
    RUN_TEST(test_get_drip_link_hash_null_ptr_manifest);
    RUN_TEST(test_get_drip_link_hash_null_ptr_hash);
    RUN_TEST(test_set_drip_link_hash_null_ptr_manifest);
    RUN_TEST(test_set_drip_link_hash_null_ptr_hash);
    RUN_TEST(test_set_and_get_drip_link_hash);
    RUN_TEST(test_get_det_null_ptr_manifest);
    RUN_TEST(test_get_det_null_ptr_det);
    RUN_TEST(test_set_det_null_ptr_manifest);
    RUN_TEST(test_set_det_null_ptr_det);
    RUN_TEST(test_set_and_get_det);
    RUN_TEST(test_get_signature_null_ptr_manifest);
    RUN_TEST(test_get_signature_null_ptr_sig);
    RUN_TEST(test_set_signature_null_ptr_manifest);
    RUN_TEST(test_set_signature_null_ptr_sig);
    RUN_TEST(test_set_and_get_signature);
    RUN_TEST(test_add_message_hash_null_ptr_manifest);
    RUN_TEST(test_add_message_hash_null_ptr_hash);
    RUN_TEST(test_add_message_hash_array_full);
    RUN_TEST(test_add_message_hash_success);
}
