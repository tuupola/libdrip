#include <string.h>

#include "drip/format.h"
#include "drip/link.h"
#include "drip/manifest.h"
#include "drip/union.h"
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

TEST test_decode_null_ptr(void) {
    drip_format_t format;
    uint8_t buffer[1];

    buffer[0] = DRIP_SAM_TYPE_LINK;

    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, drip_format_decode(NULL, buffer, sizeof(buffer)));
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, drip_format_decode(&format, NULL, sizeof(buffer)));
    PASS();
}

TEST test_decode_empty_buffer(void) {
    drip_format_t format;
    uint8_t buffer[1];
    int rc;

    buffer[0] = DRIP_SAM_TYPE_LINK;
    rc = drip_format_decode(&format, buffer, 0);
    ASSERT_EQ(DRIP_ERROR_BUFFER_TOO_SMALL, rc);
    PASS();
}

TEST test_decode_invalid_sam_type(void) {
    drip_format_t format;
    drip_format_t original;
    uint8_t buffer[1];
    int rc;

    buffer[0] = 0xFF;
    memset(&format, 0xA5, sizeof(format));
    memcpy(&original, &format, sizeof(format));

    rc = drip_format_decode(&format, buffer, sizeof(buffer));
    ASSERT_EQ(DRIP_ERROR_INVALID_SAM_TYPE, rc);
    ASSERT_MEM_EQ(&original, &format, sizeof(format));

    PASS();
}

TEST test_decode_link(void) {
    drip_link_t link;
    drip_link_t expected;
    drip_format_t actual;
    uint8_t buffer[DRIP_LINK_SIZE];
    uint8_t sam_type;
    size_t length = 0;
    int rc;

    drip_link_init(&link);
    drip_link_set_vnb(&link, 10);
    ASSERT_EQ(DRIP_SUCCESS, drip_link_encode(&link, buffer, sizeof(buffer), &length));

    rc = drip_link_decode(&expected, buffer, length);
    ASSERT_EQ(DRIP_SUCCESS, rc);

    rc = drip_format_decode(&actual, buffer, length);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    memcpy(&sam_type, &actual, sizeof(sam_type));
    ASSERT_EQ(DRIP_SAM_TYPE_LINK, sam_type);
    ASSERT_MEM_EQ(&expected, &actual, sizeof(drip_link_t));
    PASS();
}

TEST test_decode_wrapper(void) {
    drip_wrapper_t wrapper;
    drip_wrapper_t expected;
    drip_format_t actual;
    uint8_t buffer[DRIP_WRAPPER_MAX_SIZE];
    uint8_t sam_type;
    size_t length = 0;
    int rc;

    drip_wrapper_init(&wrapper);
    drip_wrapper_set_vnb(&wrapper, 10);
    ASSERT_EQ(
        DRIP_SUCCESS, drip_wrapper_encode(&wrapper, buffer, sizeof(buffer), &length)
    );

    rc = drip_wrapper_decode(&expected, buffer, length);
    ASSERT_EQ(DRIP_SUCCESS, rc);

    rc = drip_format_decode(&actual, buffer, length);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    memcpy(&sam_type, &actual, sizeof(sam_type));
    ASSERT_EQ(DRIP_SAM_TYPE_WRAPPER, sam_type);
    ASSERT_MEM_EQ(&expected, &actual, sizeof(drip_wrapper_t));
    PASS();
}

TEST test_decode_manifest(void) {
    drip_manifest_t manifest;
    drip_manifest_t expected;
    drip_format_t actual;
    uint8_t buffer[DRIP_MANIFEST_MAX_SIZE];
    uint8_t sam_type;
    size_t length = 0;
    int rc;

    drip_manifest_init(&manifest);
    drip_manifest_set_vnb(&manifest, 10);
    ASSERT_EQ(
        DRIP_SUCCESS, drip_manifest_encode(&manifest, buffer, sizeof(buffer), &length)
    );

    rc = drip_manifest_decode(&expected, buffer, length);
    ASSERT_EQ(DRIP_SUCCESS, rc);

    rc = drip_format_decode(&actual, buffer, length);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    memcpy(&sam_type, &actual, sizeof(sam_type));
    ASSERT_EQ(DRIP_SAM_TYPE_MANIFEST, sam_type);
    ASSERT_MEM_EQ(&expected, &actual, sizeof(drip_manifest_t));
    PASS();
}

TEST test_decode_invalid_length(void) {
    drip_format_t format;
    uint8_t buffer[DRIP_WRAPPER_MIN_SIZE + 1];
    int rc;

    memset(buffer, 0, sizeof(buffer));
    buffer[0] = DRIP_SAM_TYPE_WRAPPER;

    rc = drip_format_decode(&format, buffer, sizeof(buffer));
    ASSERT_EQ(DRIP_ERROR_INVALID_LENGTH, rc);
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
    RUN_TEST(test_decode_null_ptr);
    RUN_TEST(test_decode_empty_buffer);
    RUN_TEST(test_decode_invalid_sam_type);
    RUN_TEST(test_decode_link);
    RUN_TEST(test_decode_wrapper);
    RUN_TEST(test_decode_manifest);
    RUN_TEST(test_decode_invalid_length);
}
