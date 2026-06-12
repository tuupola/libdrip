#include <stdint.h>
#include <string.h>

#include "drip/det.h"
#include "unit.h"

TEST test_init_null_pointer(void) {
    int rc = drip_det_init(NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_init(void) {
    drip_det_t det;

    int rc = drip_det_init(&det);
    ASSERT_EQ(DRIP_SUCCESS, rc);

    ASSERT_EQ(0x20, det[0]);
    ASSERT_EQ(0x01, det[1]);
    ASSERT_EQ(0x00, det[2]);
    ASSERT_EQ(0x30, det[3]);

    for (int i = 4; i < DRIP_DET_SIZE; i++) {
        ASSERT_EQ(0, det[i]);
    }
    PASS();
}

TEST test_set_raa_null_pointer(void) {
    int rc = drip_det_set_raa(NULL, 1);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_get_raa_null_pointer(void) {
    uint16_t raa = drip_det_get_raa(NULL);
    ASSERT_EQ(0, raa);
    PASS();
}

TEST test_set_raa_out_of_range(void) {
    drip_det_t det;
    drip_det_init(&det);

    int rc = drip_det_set_raa(&det, 0x4000);
    ASSERT_EQ(DRIP_ERROR_OUT_OF_RANGE, rc);
    PASS();
}

TEST test_set_and_get_raa(void) {
    drip_det_t det;
    drip_det_init(&det);

    int rc = drip_det_set_raa(&det, 16376);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_EQ(16376, drip_det_get_raa(&det));

    rc = drip_det_set_raa(&det, 0x3FFF);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_EQ(0x3FFF, drip_det_get_raa(&det));

    rc = drip_det_set_raa(&det, 0);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_EQ(0, drip_det_get_raa(&det));
    PASS();
}

/* RFC 9374 example DET 2001:30:280:1405:a3ad:1952:ad0:a69e has RAA = 10 */
/* https://www.rfc-editor.org/info/rfc9374/#name-det-encoding-example */
/* https://www.rfc-editor.org/info/rfc9374/#HHIT_DNS */
TEST test_get_raa_rfc_9374_example(void) {
    drip_det_t det = {
        0x20, 0x01, 0x00, 0x30, 0x02, 0x80, 0x14, 0x05,
        0xa3, 0xad, 0x19, 0x52, 0x0a, 0xd0, 0xa6, 0x9e
    };

    ASSERT_EQ(10, drip_det_get_raa(&det));
    PASS();
}

TEST test_set_hda_null_pointer(void) {
    int rc = drip_det_set_hda(NULL, 1);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_get_hda_null_pointer(void) {
    uint16_t hda = drip_det_get_hda(NULL);
    ASSERT_EQ(0, hda);
    PASS();
}

TEST test_set_hda_out_of_range(void) {
    drip_det_t det;
    drip_det_init(&det);

    int rc = drip_det_set_hda(&det, 0x4000);
    ASSERT_EQ(DRIP_ERROR_OUT_OF_RANGE, rc);
    PASS();
}

TEST test_set_and_get_hda(void) {
    drip_det_t det;
    drip_det_init(&det);

    int rc = drip_det_set_hda(&det, 16376);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_EQ(16376, drip_det_get_hda(&det));

    rc = drip_det_set_hda(&det, 0x3FFF);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_EQ(0x3FFF, drip_det_get_hda(&det));

    rc = drip_det_set_hda(&det, 0);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_EQ(0, drip_det_get_hda(&det));
    PASS();
}

/* RFC 9374 example DET 2001:30:280:1405:a3ad:1952:ad0:a69e has HDA = 20 */
TEST test_get_hda_rfc_9374_example(void) {
    drip_det_t det = {
        0x20, 0x01, 0x00, 0x30, 0x02, 0x80, 0x14, 0x05,
        0xa3, 0xad, 0x19, 0x52, 0x0a, 0xd0, 0xa6, 0x9e
    };

    ASSERT_EQ(20, drip_det_get_hda(&det));
    PASS();
}

TEST test_set_hid_null_pointer(void) {
    int rc = drip_det_set_hid(NULL, 1);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_get_hid_null_pointer(void) {
    uint32_t hid = drip_det_get_hid(NULL);
    ASSERT_EQ(0, hid);
    PASS();
}

TEST test_set_hid_out_of_range(void) {
    drip_det_t det;
    drip_det_init(&det);

    int rc = drip_det_set_hid(&det, 0x10000000);
    ASSERT_EQ(DRIP_ERROR_OUT_OF_RANGE, rc);
    PASS();
}

TEST test_set_and_get_hid(void) {
    drip_det_t det;
    drip_det_init(&det);

    int rc = drip_det_set_hid(&det, 0x0FFFFFFF);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_EQ(0x0FFFFFFF, drip_det_get_hid(&det));

    rc = drip_det_set_hid(&det, 0x1234567);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_EQ(0x1234567, drip_det_get_hid(&det));

    rc = drip_det_set_hid(&det, 0);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_EQ(0, drip_det_get_hid(&det));
    PASS();
}

/* RFC 9374 example DET 2001:30:280:1405:a3ad:1952:ad0:a69e has HID = 163860 */
TEST test_get_hid_rfc_9374_example(void) {
    drip_det_t det = {
        0x20, 0x01, 0x00, 0x30, 0x02, 0x80, 0x14, 0x05,
        0xa3, 0xad, 0x19, 0x52, 0x0a, 0xd0, 0xa6, 0x9e
    };

    ASSERT_EQ(163860, drip_det_get_hid(&det));
    PASS();
}

TEST test_hid_with_raa_hda(void) {
    drip_det_t det;
    drip_det_init(&det);

    drip_det_set_raa(&det, 10);
    drip_det_set_hda(&det, 20);
    ASSERT_EQ(((10 << 14) | 20), drip_det_get_hid(&det));

    drip_det_set_hid(&det, 163860);
    ASSERT_EQ(10, drip_det_get_raa(&det));
    ASSERT_EQ(20, drip_det_get_hda(&det));
    PASS();
}

TEST test_set_hhsi_null_pointer(void) {
    int rc = drip_det_set_hhsi(NULL, 1);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_get_hhsi_null_pointer(void) {
    uint8_t hhsi = drip_det_get_hhsi(NULL);
    ASSERT_EQ(0, hhsi);
    PASS();
}

TEST test_set_and_get_hhsi(void) {
    drip_det_t det;
    drip_det_init(&det);

    int rc = drip_det_set_hhsi(&det, 5);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_EQ(5, drip_det_get_hhsi(&det));

    rc = drip_det_set_hhsi(&det, 0xFF);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_EQ(0xFF, drip_det_get_hhsi(&det));

    rc = drip_det_set_hhsi(&det, 0);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_EQ(0, drip_det_get_hhsi(&det));
    PASS();
}

/* RFC 9374 example DET 2001:30:280:1405:a3ad:1952:ad0:a69e has HHSI = 5 */
TEST test_get_hhsi_rfc_9374_example(void) {
    drip_det_t det = {
        0x20, 0x01, 0x00, 0x30, 0x02, 0x80, 0x14, 0x05,
        0xa3, 0xad, 0x19, 0x52, 0x0a, 0xd0, 0xa6, 0x9e
    };

    ASSERT_EQ(5, drip_det_get_hhsi(&det));
    PASS();
}

TEST test_set_hash_null_pointer(void) {
    drip_hash_t hash = {0};
    int rc = drip_det_set_hash(NULL, &hash);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_set_hash_null_hash(void) {
    drip_det_t det;
    drip_det_init(&det);

    int rc = drip_det_set_hash(&det, NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_get_hash_null_pointer(void) {
    const drip_hash_t *hash = drip_det_get_hash(NULL);
    ASSERT_EQ(NULL, hash);
    PASS();
}

TEST test_set_and_get_hash(void) {
    drip_det_t det;
    drip_det_init(&det);

    drip_hash_t hash = {0xa3, 0xad, 0x19, 0x52, 0x0a, 0xd0, 0xa6, 0x9e};

    int rc = drip_det_set_hash(&det, &hash);
    ASSERT_EQ(DRIP_SUCCESS, rc);

    const drip_hash_t *result = drip_det_get_hash(&det);
    ASSERT_MEM_EQ(hash, *result, sizeof(drip_hash_t));
    PASS();
}

/* RFC 9374 example DET 2001:30:280:1405:a3ad:1952:ad0:a69e has ORCHID hash = a3ad19520ad0a69e */
TEST test_get_hash_rfc_9374_example(void) {
    drip_det_t det = {
        0x20, 0x01, 0x00, 0x30, 0x02, 0x80, 0x14, 0x05,
        0xa3, 0xad, 0x19, 0x52, 0x0a, 0xd0, 0xa6, 0x9e
    };

    const drip_hash_t *hash = drip_det_get_hash(&det);
    uint8_t expected[] = {0xa3, 0xad, 0x19, 0x52, 0x0a, 0xd0, 0xa6, 0x9e};
    ASSERT_MEM_EQ(expected, *hash, sizeof(drip_hash_t));
    PASS();
}

TEST test_validate_null_pointer(void) {
    int rc = drip_det_validate(NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_validate_valid_det(void) {
    drip_det_t det;
    drip_det_init(&det);

    int rc = drip_det_validate(&det);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    PASS();
}

TEST test_validate_invalid_prefix(void) {
    drip_det_t det;
    drip_det_init(&det);

    det[0] = 0xFF;
    int rc = drip_det_validate(&det);
    ASSERT_EQ(DRIP_ERROR_INVALID_IPV6_PREFIX, rc);

    drip_det_init(&det);
    det[1] = 0xFF;
    rc = drip_det_validate(&det);
    ASSERT_EQ(DRIP_ERROR_INVALID_IPV6_PREFIX, rc);

    drip_det_init(&det);
    det[2] = 0xFF;
    rc = drip_det_validate(&det);
    ASSERT_EQ(DRIP_ERROR_INVALID_IPV6_PREFIX, rc);

    drip_det_init(&det);
    det[3] = 0xFF;
    rc = drip_det_validate(&det);
    ASSERT_EQ(DRIP_ERROR_INVALID_IPV6_PREFIX, rc);
    PASS();
}

SUITE(det_suite) {
    RUN_TEST(test_init_null_pointer);
    RUN_TEST(test_init);
    RUN_TEST(test_set_raa_null_pointer);
    RUN_TEST(test_get_raa_null_pointer);
    RUN_TEST(test_set_raa_out_of_range);
    RUN_TEST(test_set_and_get_raa);
    RUN_TEST(test_get_raa_rfc_9374_example);
    RUN_TEST(test_set_hda_null_pointer);
    RUN_TEST(test_get_hda_null_pointer);
    RUN_TEST(test_set_hda_out_of_range);
    RUN_TEST(test_set_and_get_hda);
    RUN_TEST(test_get_hda_rfc_9374_example);
    RUN_TEST(test_set_hid_null_pointer);
    RUN_TEST(test_get_hid_null_pointer);
    RUN_TEST(test_set_hid_out_of_range);
    RUN_TEST(test_set_and_get_hid);
    RUN_TEST(test_get_hid_rfc_9374_example);
    RUN_TEST(test_hid_with_raa_hda);
    RUN_TEST(test_set_hhsi_null_pointer);
    RUN_TEST(test_get_hhsi_null_pointer);
    RUN_TEST(test_set_and_get_hhsi);
    RUN_TEST(test_get_hhsi_rfc_9374_example);
    RUN_TEST(test_set_hash_null_pointer);
    RUN_TEST(test_set_hash_null_hash);
    RUN_TEST(test_get_hash_null_pointer);
    RUN_TEST(test_set_and_get_hash);
    RUN_TEST(test_get_hash_rfc_9374_example);
}
