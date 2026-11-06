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

/* Reject a wrapper if sam_type is not a wrapper. */
TEST test_validate_invalid_sam_type(void) {
    drip_wrapper_t wrapper;

    drip_wrapper_init(&wrapper);
    drip_wrapper_set_det(&wrapper, &valid_det);
    wrapper.sam_type = 0;
    ASSERT_EQ(DRIP_ERROR_INVALID_SAM_TYPE, drip_wrapper_validate(&wrapper));
    PASS();
}

/* Reject a wrapper if vnb is after vna. */
TEST test_validate_invalid_timestamp(void) {
    drip_wrapper_t wrapper;

    drip_wrapper_init(&wrapper);
    drip_wrapper_set_det(&wrapper, &valid_det);
    drip_wrapper_set_vnb(&wrapper, 2);
    drip_wrapper_set_vna(&wrapper, 1);
    ASSERT_EQ(DRIP_ERROR_INVALID_TIMESTAMP, drip_wrapper_validate(&wrapper));
    PASS();
}

/* Reject a wrapper with an invalid det. */
TEST test_validate_invalid_det(void) {
    drip_wrapper_t wrapper;

    drip_wrapper_init(&wrapper);
    ASSERT_EQ(DRIP_ERROR_INVALID_DET, drip_wrapper_validate(&wrapper));
    PASS();
}

/* Reject a wrapper if evidence_count exceeds the maximum. */
TEST test_validate_evidence_overflow(void) {
    drip_wrapper_t wrapper;

    drip_wrapper_init(&wrapper);
    drip_wrapper_set_det(&wrapper, &valid_det);
    wrapper.evidence_count = DRIP_WRAPPER_EVIDENCE_MAX + 1;
    ASSERT_EQ(DRIP_ERROR_ARRAY_OVERFLOW, drip_wrapper_validate(&wrapper));
    PASS();
}

/* Reject encoding a wrapper if evidence_count exceeds the maximum. */
TEST test_encode_evidence_overflow(void) {
    drip_wrapper_t wrapper;
    uint8_t buffer[DRIP_WRAPPER_MAX_SIZE];
    size_t encoded_length;

    drip_wrapper_init(&wrapper);
    wrapper.evidence_count = DRIP_WRAPPER_EVIDENCE_MAX + 1;
    encoded_length = 0;
    ASSERT_EQ(
        DRIP_ERROR_ARRAY_OVERFLOW,
        drip_wrapper_encode(&wrapper, buffer, sizeof(buffer), &encoded_length)
    );
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

static int sign_mark_called(
    void *context, const uint8_t *input, size_t input_length, uint8_t *buffer,
    size_t buffer_size, size_t *output_length
) {
    int *called = context;

    (void)input;
    (void)input_length;
    (void)buffer;
    (void)buffer_size;
    (void)output_length;
    *called = 1;
    return 0;
}

/* Do not call the callback if validation fails. */
TEST test_sign_invalid_input(void) {
    drip_wrapper_t wrapper;
    int called = 0;

    drip_wrapper_init(&wrapper);
    ASSERT_EQ(
        DRIP_ERROR_INVALID_DET, drip_wrapper_sign(&wrapper, sign_mark_called, &called)
    );
    ASSERT_EQ(0, called);
    PASS();
}

static int verify_success(
    void *context, const uint8_t *input, size_t input_length, const uint8_t *signature,
    size_t signature_length
) {
    (void)context;
    (void)input;
    (void)input_length;
    (void)signature;
    (void)signature_length;
    return 0;
}

static int verify_mark_called(
    void *context, const uint8_t *input, size_t input_length, const uint8_t *signature,
    size_t signature_length
) {
    int *called = context;

    (void)input;
    (void)input_length;
    (void)signature;
    (void)signature_length;
    *called = 1;
    return 0;
}

/* Do not call the callback if validation fails. */
TEST test_verify_invalid_input(void) {
    drip_wrapper_t wrapper;
    int called = 0;

    drip_wrapper_init(&wrapper);
    ASSERT_EQ(
        DRIP_ERROR_INVALID_DET,
        drip_wrapper_verify(&wrapper, 0, verify_mark_called, &called)
    );
    ASSERT_EQ(0, called);
    PASS();
}

/* Verify a structurally valid wrapper. */
TEST test_verify_success(void) {
    drip_wrapper_t wrapper;

    drip_wrapper_init(&wrapper);
    drip_wrapper_set_det(&wrapper, &valid_det);
    ASSERT_EQ(DRIP_SUCCESS, drip_wrapper_verify(&wrapper, 0, verify_success, NULL));
    PASS();
}

/* Ignore the time window when unixtime is 0. */
TEST test_verify_unixtime_skipped(void) {
    drip_wrapper_t wrapper;

    drip_wrapper_init(&wrapper);
    drip_wrapper_set_det(&wrapper, &valid_det);
    drip_wrapper_set_vnb_unixtime(&wrapper, 1546300800);
    drip_wrapper_set_vna_unixtime(&wrapper, 1546300900);
    ASSERT_EQ(DRIP_SUCCESS, drip_wrapper_verify(&wrapper, 0, verify_success, NULL));
    PASS();
}

/* Accept unixtime at vnb, inside the window and at vna. */
TEST test_verify_unixtime_success(void) {
    drip_wrapper_t wrapper;
    uint32_t vnb, vna;

    drip_wrapper_init(&wrapper);
    drip_wrapper_set_det(&wrapper, &valid_det);
    drip_wrapper_set_vnb_unixtime(&wrapper, 1546300800);
    drip_wrapper_set_vna_unixtime(&wrapper, 1546300900);
    vnb = drip_wrapper_get_vnb_unixtime(&wrapper);
    vna = drip_wrapper_get_vna_unixtime(&wrapper);

    ASSERT_EQ(DRIP_SUCCESS, drip_wrapper_verify(&wrapper, vnb, verify_success, NULL));
    ASSERT_EQ(
        DRIP_SUCCESS,
        drip_wrapper_verify(&wrapper, vnb + (vna - vnb) / 2, verify_success, NULL)
    );
    ASSERT_EQ(DRIP_SUCCESS, drip_wrapper_verify(&wrapper, vna, verify_success, NULL));
    PASS();
}

/* Reject unixtime before vnb and do not call the callback. */
TEST test_verify_unixtime_not_yet_valid(void) {
    drip_wrapper_t wrapper;
    uint32_t vnb;
    int called;

    drip_wrapper_init(&wrapper);
    drip_wrapper_set_det(&wrapper, &valid_det);
    drip_wrapper_set_vnb_unixtime(&wrapper, 1546300800);
    drip_wrapper_set_vna_unixtime(&wrapper, 1546300900);
    vnb = drip_wrapper_get_vnb_unixtime(&wrapper);
    called = 0;
    ASSERT_EQ(
        DRIP_ERROR_TIMESTAMP_NOT_YET_VALID,
        drip_wrapper_verify(&wrapper, vnb - 1, verify_mark_called, &called)
    );
    ASSERT_EQ(0, called);
    PASS();
}

/* Reject unixtime after vna and do not call the callback. */
TEST test_verify_unixtime_expired(void) {
    drip_wrapper_t wrapper;
    uint32_t vna;
    int called;

    drip_wrapper_init(&wrapper);
    drip_wrapper_set_det(&wrapper, &valid_det);
    drip_wrapper_set_vnb_unixtime(&wrapper, 1546300800);
    drip_wrapper_set_vna_unixtime(&wrapper, 1546300900);
    vna = drip_wrapper_get_vna_unixtime(&wrapper);
    called = 0;
    ASSERT_EQ(
        DRIP_ERROR_TIMESTAMP_EXPIRED,
        drip_wrapper_verify(&wrapper, vna + 1, verify_mark_called, &called)
    );
    ASSERT_EQ(0, called);
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
    RUN_TEST(test_validate_invalid_sam_type);
    RUN_TEST(test_validate_invalid_timestamp);
    RUN_TEST(test_validate_invalid_det);
    RUN_TEST(test_validate_evidence_overflow);
    RUN_TEST(test_encode_evidence_overflow);
    RUN_TEST(test_validate_success);
    RUN_TEST(test_sign_invalid_output_length);
    RUN_TEST(test_sign_invalid_input);
    RUN_TEST(test_verify_invalid_input);
    RUN_TEST(test_verify_success);
    RUN_TEST(test_verify_unixtime_skipped);
    RUN_TEST(test_verify_unixtime_success);
    RUN_TEST(test_verify_unixtime_not_yet_valid);
    RUN_TEST(test_verify_unixtime_expired);
}
