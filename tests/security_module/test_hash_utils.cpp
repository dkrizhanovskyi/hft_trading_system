#include <iostream>
#include <cassert>
#include <cstring>
#include "hash_utils.h"

// Test: Initialization and freeing of hash result structure
void test_hash_result_init_and_free() {
    hash_result_t result;

    // Initialize result for SHA-256
    int ret = hash_result_init(&result, HASH_ALG_SHA256);
    assert(ret == 0);
    assert(result.hash != nullptr);
    assert(result.hash_len == HASH_UTILS_SHA256_SIZE);
    std::cout << "Hash result initialization for SHA-256 successful. Length: " << result.hash_len << std::endl;

    hash_result_free(&result);
    assert(result.hash == nullptr);
    std::cout << "Hash result memory successfully freed." << std::endl;
}

// Test: Hashing data using SHA-256
void test_hash_data_sha256() {
    const char *data = "Hello, world!";
    size_t data_len = strlen(data);

    hash_result_t result;
    int ret = hash_data((const uint8_t *)data, data_len, HASH_ALG_SHA256, &result);
    assert(ret == 0);
    assert(result.hash != nullptr);
    assert(result.hash_len == HASH_UTILS_SHA256_SIZE);
    std::cout << "Data hashing using SHA-256 successful." << std::endl;

    // Example output of hash
    std::cout << "Hash (SHA-256): ";
    for (size_t i = 0; i < result.hash_len; ++i) {
        printf("%02x", result.hash[i]);
    }
    std::cout << std::endl;

    hash_result_free(&result);
}

// Test: Hashing data using SHA-512
void test_hash_data_sha512() {
    const char *data = "Hello, world!";
    size_t data_len = strlen(data);

    hash_result_t result;
    int ret = hash_data((const uint8_t *)data, data_len, HASH_ALG_SHA512, &result);
    assert(ret == 0);
    assert(result.hash != nullptr);
    std::cout << "Data hashing using SHA-512 successful." << std::endl;

    // Example output of hash
    std::cout << "Hash (SHA-512): ";
    for (size_t i = 0; i < result.hash_len; ++i) {
        printf("%02x", result.hash[i]);
    }
    std::cout << std::endl;

    hash_result_free(&result);
}

// Test: Verifying data integrity using SHA-256
void test_verify_hash_sha256() {
    const char *data = "Integrity check!";
    size_t data_len = strlen(data);

    // Compute hash for the data
    hash_result_t result;
    int ret = hash_data((const uint8_t *)data, data_len, HASH_ALG_SHA256, &result);
    assert(ret == 0);

    // Verify that the data hash matches the computed hash
    bool is_valid = verify_hash((const uint8_t *)data, data_len, result.hash, result.hash_len, HASH_ALG_SHA256);
    assert(is_valid);
    std::cout << "Data integrity verification using SHA-256 successful." << std::endl;

    hash_result_free(&result);
}

// Test: Verifying data integrity with incorrect hash
void test_verify_hash_failure() {
    const char *data = "Check with wrong hash!";
    size_t data_len = strlen(data);

    // Compute hash for the data
    hash_result_t result;
    int ret = hash_data((const uint8_t *)data, data_len, HASH_ALG_SHA256, &result);
    assert(ret == 0);

    // Create an incorrect hash
    uint8_t wrong_hash[HASH_UTILS_SHA256_SIZE] = {0};

    // Verify that the data hash does not match the incorrect hash
    bool is_valid = verify_hash((const uint8_t *)data, data_len, wrong_hash, HASH_UTILS_SHA256_SIZE, HASH_ALG_SHA256);
    assert(!is_valid);
    std::cout << "Integrity check with wrong hash failed as expected." << std::endl;

    hash_result_free(&result);
}

// Main function to run all tests
int main() {
    test_hash_result_init_and_free();
    test_hash_data_sha256();
    test_hash_data_sha512();
    test_verify_hash_sha256();
    test_verify_hash_failure();

    std::cout << "All tests for hashing utilities passed successfully!" << std::endl;
    return 0;
}
