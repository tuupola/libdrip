#include <stdint.h>
#include <string.h>

#include "drip/hash.h"
#include "unit.h"

/* Just dummy callback to test it is called. */
static int pass_through_callback(
    void *context,
    const uint8_t *input,
    size_t input_length,
    uint8_t *hash,
    size_t hash_size,
    size_t *hash_length
) {
    (void)context;
    (void)hash_size;
    size_t len = input_length < DRIP_HASH_SIZE ? input_length : DRIP_HASH_SIZE;
    memcpy(hash, input, len);
    *hash_length = DRIP_HASH_SIZE;
    return 0;
}

/* Just dummy callback to test it is called. */
static int failing_callback(
    void *context,
    const uint8_t *input,
    size_t input_length,
    uint8_t *hash,
    size_t hash_size,
    size_t *hash_length
) {
    (void)context;
    (void)input;
    (void)input_length;
    (void)hash;
    (void)hash_size;
    (void)hash_length;
    return -1;
}

TEST test_null_ptr_input(void) {
    uint8_t hash[DRIP_HASH_SIZE];
    int rc = drip_hash(NULL, 0, hash, sizeof(hash), pass_through_callback, NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_null_ptr_hash(void) {
    uint8_t input[] = {0x01, 0x02};
    int rc = drip_hash(input, sizeof(input), NULL, DRIP_HASH_SIZE, pass_through_callback, NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_null_ptr_callback(void) {
    uint8_t hash[DRIP_HASH_SIZE];
    uint8_t input[] = {0x01, 0x02};
    int rc = drip_hash(input, sizeof(input), hash, sizeof(hash), NULL, NULL);
    ASSERT_EQ(DRIP_ERROR_NULL_POINTER, rc);
    PASS();
}

TEST test_hash_len(void) {
    uint8_t hash[DRIP_HASH_SIZE];
    uint8_t input[] = {0x01, 0x02};
    int rc = drip_hash(input, sizeof(input), hash, DRIP_HASH_SIZE - 1, pass_through_callback, NULL);
    ASSERT_EQ(DRIP_ERROR_BUFFER_TOO_SMALL, rc);
    PASS();
}

TEST test_callback(void) {
    uint8_t hash[DRIP_HASH_SIZE];
    uint8_t input[] = {0x01, 0x02};
    int rc = drip_hash(input, sizeof(input), hash, sizeof(hash), failing_callback, NULL);
    ASSERT_EQ(DRIP_ERROR_CALLBACK_FAILED, rc);
    PASS();
}

TEST test_success(void) {
    uint8_t hash[DRIP_HASH_SIZE];
    uint8_t input[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    int rc = drip_hash(input, sizeof(input), hash, sizeof(hash), pass_through_callback, NULL);
    ASSERT_EQ(DRIP_SUCCESS, rc);
    ASSERT_MEM_EQ(input, hash, DRIP_HASH_SIZE);
    PASS();
}

SUITE(hash_suite) {
    RUN_TEST(test_null_ptr_input);
    RUN_TEST(test_null_ptr_hash);
    RUN_TEST(test_null_ptr_callback);
    RUN_TEST(test_hash_len);
    RUN_TEST(test_callback);
    RUN_TEST(test_success);
}
