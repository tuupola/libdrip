#include "drip/error.h"
#include "unit.h"

TEST test_error_to_string(void) {
    ASSERT_STR_EQ("DRIP_SUCCESS", drip_error_to_string(DRIP_SUCCESS));
    ASSERT_STR_EQ("DRIP_ERROR_INVALID_DET", drip_error_to_string(DRIP_ERROR_INVALID_DET));
    ASSERT_STR_EQ("UNKNOWN", drip_error_to_string((drip_error_t)99));
    PASS();
}

SUITE(error_suite) {
    RUN_TEST(test_error_to_string);
}
