#include "drip/format.h"
#include "drip/link.h"
#include "drip/manifest.h"
#include "drip/wrapper.h"
#include "unit.h"

TEST test_to_json_null_ptr_format(void) {
    char buffer[256];
    size_t json_length = 0;
    int rc = drip_format_to_json(NULL, buffer, sizeof(buffer), &json_length);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_to_json_null_ptr_buffer(void) {
    drip_link_t link;
    size_t json_length = 0;

    drip_link_init(&link);

    ASSERT_EQ(DRIP_SUCCESS, drip_format_to_json(&link, NULL, 0, &json_length));
    ASSERT(json_length > 0);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, drip_format_to_json(&link, NULL, 256, NULL));
    PASS();
}

TEST test_to_json_optional_json_length(void) {
    drip_link_t link;
    char buffer[1024];
    int rc;

    drip_link_init(&link);
    rc = drip_format_to_json(&link, buffer, sizeof(buffer), NULL);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    PASS();
}

TEST test_to_json_link(void) {
    drip_link_t link;
    char expected[1024];
    char actual[1024];
    int rc;

    drip_link_init(&link);

    rc = drip_link_to_json(&link, expected, sizeof(expected), NULL);
    ASSERT_EQ(DRIP_SUCCESS, rc);

    rc = drip_format_to_json(&link, actual, sizeof(actual), NULL);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_STR_EQ(expected, actual);
    PASS();
}

TEST test_to_json_wrapper(void) {
    drip_wrapper_t wrapper;
    char expected[1024];
    char actual[1024];
    int rc;

    drip_wrapper_init(&wrapper);

    rc = drip_wrapper_to_json(&wrapper, expected, sizeof(expected), NULL);
    ASSERT_EQ(DRIP_SUCCESS, rc);

    rc = drip_format_to_json(&wrapper, actual, sizeof(actual), NULL);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_STR_EQ(expected, actual);
    PASS();
}

TEST test_to_json_manifest(void) {
    drip_manifest_t manifest;
    char expected[1024];
    char actual[1024];
    int rc;

    drip_manifest_init(&manifest);

    rc = drip_manifest_to_json(&manifest, expected, sizeof(expected), NULL);
    ASSERT_EQ(DRIP_SUCCESS, rc);

    rc = drip_format_to_json(&manifest, actual, sizeof(actual), NULL);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_STR_EQ(expected, actual);
    PASS();
}

TEST test_to_json_invalid_sam_type(void) {
    drip_link_t link;
    char buffer[256];
    int rc;

    drip_link_init(&link);
    link.sam_type = DRIP_SAM_TYPE_FRAME;

    rc = drip_format_to_json(&link, buffer, sizeof(buffer), NULL);
    ASSERT_EQ(DRIP_ERROR_INVALID_SAM_TYPE, rc);

    link.sam_type = 0xFF;
    rc = drip_format_to_json(&link, buffer, sizeof(buffer), NULL);
    ASSERT_EQ(DRIP_ERROR_INVALID_SAM_TYPE, rc);
    PASS();
}

TEST test_to_json_buffer_too_small(void) {
    drip_link_t link;
    char buffer[8];
    int rc;

    drip_link_init(&link);
    rc = drip_format_to_json(&link, buffer, sizeof(buffer), NULL);
    ASSERT_EQ(DRIP_ERROR_BUFFER_TOO_SMALL, rc);
    PASS();
}

SUITE(format_suite) {
    RUN_TEST(test_to_json_null_ptr_format);
    RUN_TEST(test_to_json_null_ptr_buffer);
    RUN_TEST(test_to_json_optional_json_length);
    RUN_TEST(test_to_json_link);
    RUN_TEST(test_to_json_wrapper);
    RUN_TEST(test_to_json_manifest);
    RUN_TEST(test_to_json_invalid_sam_type);
    RUN_TEST(test_to_json_buffer_too_small);
}
