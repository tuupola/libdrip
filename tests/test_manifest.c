#include <stdint.h>
#include <string.h>

#include "unit.h"
#include <drip/manifest.h>

TEST test_init_null_pointer(void) {
    int rc = drip_manifest_init(NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_init_success(void) {
    drip_manifest_t message;

    int rc = drip_manifest_init(&message);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_EQ(DRIP_SAM_TYPE_MANIFEST, message.sam_type);
    PASS();
}

TEST test_get_vnb_null_ptr(void)
{
    uint32_t result = drip_manifest_get_vnb(NULL);
    ASSERT_EQ(0, result);
    PASS();
}

TEST test_set_vnb_null_ptr(void)
{
    int rc = drip_manifest_set_vnb(NULL, 123);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_and_get_vnb(void)
{
    drip_manifest_t message;
    uint32_t value = 123456789;

    drip_manifest_init(&message);
    int rc = drip_manifest_set_vnb(&message, value);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_EQ(value, drip_manifest_get_vnb(&message));
    PASS();
}

SUITE(manifest_suite) {
    RUN_TEST(test_init_null_pointer);
    RUN_TEST(test_init_success);
    RUN_TEST(test_get_vnb_null_ptr);
    RUN_TEST(test_set_vnb_null_ptr);
    RUN_TEST(test_set_and_get_vnb);
}
