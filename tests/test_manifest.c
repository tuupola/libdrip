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

SUITE(manifest_suite) {
    RUN_TEST(test_init_null_pointer);
    RUN_TEST(test_init_success);
}
