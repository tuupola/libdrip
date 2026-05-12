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
}
