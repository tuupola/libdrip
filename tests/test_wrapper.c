#include <stdint.h>
#include <string.h>

#include "drip/wrapper.h"
#include "unit.h"

enum rid_message_type_t {
    RID_MESSAGE_TYPE_BASIC_ID = 0x00,
    RID_MESSAGE_TYPE_LOCATION = 0x01,
    RID_MESSAGE_TYPE_AUTH = 0x02,
    RID_MESSAGE_TYPE_SELF_ID = 0x03,
    RID_MESSAGE_TYPE_SYSTEM = 0x04,
    RID_MESSAGE_TYPE_OPERATOR_ID = 0x05,
    RID_MESSAGE_TYPE_MESSAGE_PACK = 0x0F
};

static const drip_det_t valid_det = {
    0x20, 0x01, 0x00, 0x30, 0x02, 0x80, 0x14, 0x05,
    0xa3, 0xad, 0x19, 0x52, 0x0a, 0xd0, 0xa6, 0x9e,
};

/* Try to add a Basic ID message as evidence to null wrapper. */
TEST test_add_evidence_null_wrapper(void) {
    uint8_t message[RID_MESSAGE_SIZE];
    int rc;

    memset(message, 0, RID_MESSAGE_SIZE);
    message[0] = (uint8_t)(RID_MESSAGE_TYPE_BASIC_ID << 4);
    rc = drip_wrapper_add_evidence(NULL, message, RID_MESSAGE_SIZE);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

/* Try to add a null as evidence to wrapper. */
TEST test_add_evidence_null_buffer(void) {
    drip_wrapper_t wrapper;
    int rc;

    drip_wrapper_init(&wrapper);
    rc = drip_wrapper_add_evidence(&wrapper, NULL, RID_MESSAGE_SIZE);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

/* Try to add an invalid length Basic ID message as evidence to wrapper. */
TEST test_add_evidence_invalid_length(void) {
    drip_wrapper_t wrapper;
    uint8_t message[RID_MESSAGE_SIZE];
    int rc;

    memset(message, 0, RID_MESSAGE_SIZE);
    message[0] = (uint8_t)(RID_MESSAGE_TYPE_BASIC_ID << 4);
    drip_wrapper_init(&wrapper);
    rc = drip_wrapper_add_evidence(&wrapper, message, RID_MESSAGE_SIZE - 1);
    ASSERT_EQ(DRIP_ERROR_INVALID_LENGTH, rc);
    rc = drip_wrapper_add_evidence(&wrapper, message, RID_MESSAGE_SIZE + 1);
    ASSERT_EQ(DRIP_ERROR_INVALID_LENGTH, rc);
    PASS();
}

/* Try to add Auth message as evidence to wrapper. */
TEST test_add_evidence_invalid_type_auth(void) {
    drip_wrapper_t wrapper;
    uint8_t message[RID_MESSAGE_SIZE];
    int rc;

    memset(message, 0, RID_MESSAGE_SIZE);
    message[0] = (uint8_t)(RID_MESSAGE_TYPE_AUTH << 4);
    drip_wrapper_init(&wrapper);
    rc = drip_wrapper_add_evidence(&wrapper, message, RID_MESSAGE_SIZE);
    ASSERT_EQ(DRIP_ERROR_INVALID_MESSAGE_TYPE, rc);
    PASS();
}

/* Try to add Message Pack as evidence to wrapper. */
TEST test_add_evidence_invalid_type_message_pack(void) {
    drip_wrapper_t wrapper;
    uint8_t message[RID_MESSAGE_SIZE];
    int rc;

    memset(message, 0, RID_MESSAGE_SIZE);
    message[0] = (uint8_t)(RID_MESSAGE_TYPE_MESSAGE_PACK << 4);
    drip_wrapper_init(&wrapper);
    rc = drip_wrapper_add_evidence(&wrapper, message, RID_MESSAGE_SIZE);
    ASSERT_EQ(DRIP_ERROR_INVALID_MESSAGE_TYPE, rc);
    PASS();
}

/* Add all valid message types as evidence to wrapper. */
TEST test_add_evidence_all_allowed_types(void) {
    drip_wrapper_t wrapper;
    uint8_t message[RID_MESSAGE_SIZE];

    drip_wrapper_init(&wrapper);
    memset(message, 0, RID_MESSAGE_SIZE);
    message[0] = (uint8_t)(RID_MESSAGE_TYPE_BASIC_ID << 4);
    ASSERT_EQ(
        DRIP_SUCCESS, drip_wrapper_add_evidence(&wrapper, message, RID_MESSAGE_SIZE)
    );
    memset(message, 0, RID_MESSAGE_SIZE);
    message[0] = (uint8_t)(RID_MESSAGE_TYPE_LOCATION << 4);
    ASSERT_EQ(
        DRIP_SUCCESS, drip_wrapper_add_evidence(&wrapper, message, RID_MESSAGE_SIZE)
    );
    memset(message, 0, RID_MESSAGE_SIZE);
    message[0] = (uint8_t)(RID_MESSAGE_TYPE_SELF_ID << 4);
    ASSERT_EQ(
        DRIP_SUCCESS, drip_wrapper_add_evidence(&wrapper, message, RID_MESSAGE_SIZE)
    );
    ASSERT_EQ(3, drip_wrapper_evidence_count(&wrapper));
    PASS();
}

/* Try to validate a null pointer. */
TEST test_validate_null_pointer(void) {
    int rc;

    rc = drip_wrapper_validate(NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

/* Try to validate wrapper with Auth message as evidence. */
TEST test_validate_invalid_message_type(void) {
    drip_wrapper_t wrapper;
    uint8_t message[RID_MESSAGE_SIZE];
    int rc;

    drip_wrapper_init(&wrapper);
    drip_wrapper_set_det(&wrapper, &valid_det);
    memset(message, 0, RID_MESSAGE_SIZE);
    message[0] = (uint8_t)(RID_MESSAGE_TYPE_AUTH << 4);
    memcpy(wrapper.evidence[0], message, RID_MESSAGE_SIZE);
    wrapper.evidence_count = 1;

    rc = drip_wrapper_validate(&wrapper);
    ASSERT_EQ(DRIP_ERROR_INVALID_MESSAGE_TYPE, rc);
    PASS();
}

static int sign_wrong_length(
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

/* Reject a signature whose reported length is not DRIP_SIGNATURE_SIZE. */
TEST test_sign_invalid_output_length(void) {
    drip_wrapper_t wrapper;

    drip_wrapper_init(&wrapper);
    drip_wrapper_set_det(&wrapper, &valid_det);
    int rc = drip_wrapper_sign(&wrapper, sign_wrong_length, NULL);
    ASSERT_EQ(DRIP_ERROR_INVALID_LENGTH, rc);
    PASS();
}

/* Reject signing if sam_type is not a wrapper. */
TEST test_sign_invalid_sam_type(void) {
    drip_wrapper_t wrapper;

    drip_wrapper_init(&wrapper);
    drip_wrapper_set_det(&wrapper, &valid_det);
    wrapper.sam_type = 0;
    ASSERT_EQ(
        DRIP_ERROR_INVALID_SAM_TYPE, drip_wrapper_sign(&wrapper, sign_wrong_length, NULL)
    );
    PASS();
}

/* Reject signing if vnb is after vna. */
TEST test_sign_invalid_timestamp(void) {
    drip_wrapper_t wrapper;

    drip_wrapper_init(&wrapper);
    drip_wrapper_set_det(&wrapper, &valid_det);
    drip_wrapper_set_vnb(&wrapper, 2);
    drip_wrapper_set_vna(&wrapper, 1);
    ASSERT_EQ(
        DRIP_ERROR_INVALID_TIMESTAMP, drip_wrapper_sign(&wrapper, sign_wrong_length, NULL)
    );
    PASS();
}

/* Reject signing with invalid evidence type. */
TEST test_sign_invalid_message_type(void) {
    drip_wrapper_t wrapper;
    uint8_t message[RID_MESSAGE_SIZE];

    drip_wrapper_init(&wrapper);
    drip_wrapper_set_det(&wrapper, &valid_det);
    memset(message, 0, RID_MESSAGE_SIZE);
    message[0] = (uint8_t)(RID_MESSAGE_TYPE_AUTH << 4);
    memcpy(wrapper.evidence[0], message, RID_MESSAGE_SIZE);
    wrapper.evidence_count = 1;
    ASSERT_EQ(
        DRIP_ERROR_INVALID_MESSAGE_TYPE,
        drip_wrapper_sign(&wrapper, sign_wrong_length, NULL)
    );
    PASS();
}

/* Reject signing with invalid det. */
TEST test_sign_invalid_det(void) {
    drip_wrapper_t wrapper;

    drip_wrapper_init(&wrapper);
    ASSERT_EQ(
        DRIP_ERROR_INVALID_DET, drip_wrapper_sign(&wrapper, sign_wrong_length, NULL)
    );
    PASS();
}

/* Reject signing if evidence_count exceeds the maximum. */
TEST test_sign_evidence_overflow(void) {
    drip_wrapper_t wrapper;

    drip_wrapper_init(&wrapper);
    drip_wrapper_set_det(&wrapper, &valid_det);
    wrapper.evidence_count = DRIP_WRAPPER_EVIDENCE_MAX + 1;
    ASSERT_EQ(
        DRIP_ERROR_ARRAY_OVERFLOW, drip_wrapper_sign(&wrapper, sign_wrong_length, NULL)
    );
    PASS();
}

/* Validate a valid wrapper. */
TEST test_validate_success(void) {
    drip_wrapper_t wrapper;

    drip_wrapper_init(&wrapper);
    drip_wrapper_set_det(&wrapper, &valid_det);
    ASSERT_EQ(DRIP_SUCCESS, drip_wrapper_validate(&wrapper));
    PASS();
}

SUITE(wrapper_suite) {
    RUN_TEST(test_add_evidence_null_wrapper);
    RUN_TEST(test_add_evidence_null_buffer);
    RUN_TEST(test_add_evidence_invalid_length);
    RUN_TEST(test_add_evidence_invalid_type_auth);
    RUN_TEST(test_add_evidence_invalid_type_message_pack);
    RUN_TEST(test_add_evidence_all_allowed_types);
    RUN_TEST(test_validate_null_pointer);
    RUN_TEST(test_validate_invalid_message_type);
    RUN_TEST(test_validate_success);
    RUN_TEST(test_sign_invalid_output_length);
    RUN_TEST(test_sign_invalid_sam_type);
    RUN_TEST(test_sign_invalid_timestamp);
    RUN_TEST(test_sign_invalid_message_type);
    RUN_TEST(test_sign_invalid_det);
    RUN_TEST(test_sign_evidence_overflow);
}
