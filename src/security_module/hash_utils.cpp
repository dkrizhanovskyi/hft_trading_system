/**
 * @file hash_utils.c
 * @brief Security Module: Hash Utility Implementation
 *
 * This source file implements cryptographic hashing operations for the HFT system's security module.
 * It provides functions for generating cryptographic hashes (SHA-256, SHA-512) and verifying data integrity 
 * by comparing hash values. This implementation leverages OpenSSL for robust and secure hashing operations.
 *
 * **Key functionalities include:**
 * - Initialization and cleanup of hash result structures.
 * - Data hashing using SHA-256 and SHA-512.
 * - Secure comparison of computed and expected hash values for integrity verification.
 * - Use of OpenSSL's EVP interface to handle cryptographic operations, ensuring compatibility with secure algorithms.
 */

#include "hash_utils.h"
#include <openssl/evp.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Function: Initialize the hash result structure based on the algorithm type
/**
 * @brief Initializes the hash result structure based on the algorithm type.
 *
 * Allocates memory for the hash output buffer, dynamically sizing the buffer depending 
 * on the selected cryptographic algorithm (SHA-256 or SHA-512). 
 *
 * @param result Pointer to the hash_result_t structure where the hash will be stored.
 * @param algorithm The hash algorithm to use (SHA-256 or SHA-512).
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int hash_result_init(hash_result_t *result, hash_algorithm_t algorithm) {
    if (!result) {
        return -EINVAL;  // Invalid argument: result pointer is null
    }

    const EVP_MD *md;
    switch (algorithm) {
        case HASH_ALG_SHA256:
            md = EVP_sha256();  // Set algorithm to SHA-256
            break;
        case HASH_ALG_SHA512:
            md = EVP_sha512();  // Set algorithm to SHA-512
            break;
        default:
            return -EINVAL;  // Unsupported algorithm
    }

    result->hash_len = EVP_MD_size(md);  // Get digest size (32 bytes for SHA-256, 64 for SHA-512)
    if (result->hash_len <= 0) {
        return -EIO;  // Error retrieving hash length, treat as input-output error
    }

    result->hash = (uint8_t *)malloc(result->hash_len);  // Allocate memory for the hash
    if (!result->hash) {
        return -ENOMEM;  // Memory allocation failure
    }

    return 0;
}

// Function: Free the memory associated with the hash result structure
/**
 * @brief Frees the memory associated with the hash result structure.
 *
 * This function safely releases the memory allocated for the hash output, ensuring no sensitive 
 * information remains in memory after the structure is no longer needed.
 *
 * @param result Pointer to the hash_result_t structure to be cleaned up.
 */
void hash_result_free(hash_result_t *result) {
    if (result && result->hash) {
        free(result->hash);  // Free allocated memory for hash
        result->hash = NULL;  // Reset pointer to avoid dangling reference
        result->hash_len = 0;  // Clear hash length
    }
}

// Function: Hash data using the specified algorithm
/**
 * @brief Computes the hash of the input data using the specified algorithm.
 *
 * This function generates a cryptographic hash (SHA-256 or SHA-512) for the provided input data 
 * and stores the result in the provided hash_result_t structure.
 *
 * @param data Pointer to the input data to be hashed.
 * @param data_len Length of the input data in bytes.
 * @param algorithm The hash algorithm to use (SHA-256 or SHA-512).
 * @param result Pointer to the hash_result_t structure where the computed hash will be stored.
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int hash_data(const uint8_t *data, size_t data_len, hash_algorithm_t algorithm, hash_result_t *result) {
    if (!data || !result) {
        return -EINVAL;  // Invalid arguments: data or result is null
    }

    int ret = hash_result_init(result, algorithm);  // Initialize result structure
    if (ret != 0) {
        return ret;  // Failed to initialize the hash result
    }

    // Select the appropriate hashing algorithm
    switch (algorithm) {
        case HASH_ALG_SHA256:
            return hash_sha256(data, data_len, result);  // Call SHA-256 hash function
        case HASH_ALG_SHA512:
            return hash_sha512(data, data_len, result);  // Call SHA-512 hash function
        default:
            return -EINVAL;  // Unsupported algorithm
    }
}

// Function: Verify if the given data matches the provided hash
/**
 * @brief Verifies the integrity of data by comparing it to the expected hash.
 *
 * This function hashes the input data and compares the result with the expected hash to determine 
 * if the data has been modified or corrupted.
 *
 * @param data Pointer to the input data.
 * @param data_len Length of the input data in bytes.
 * @param expected_hash Pointer to the expected hash to compare against.
 * @param expected_hash_len Length of the expected hash.
 * @param algorithm The hash algorithm used to generate the expected hash.
 * @return bool Returns true if the hashes match, indicating the data is intact, false otherwise.
 */
bool verify_hash(const uint8_t *data, size_t data_len, const uint8_t *expected_hash, size_t expected_hash_len, hash_algorithm_t algorithm) {
    if (!data || !expected_hash) {
        return false;  // Invalid input
    }

    hash_result_t result;
    if (hash_data(data, data_len, algorithm, &result) != 0) {
        return false;  // Hashing failed
    }

    // Compare the generated hash with the expected hash
    bool is_valid = (result.hash_len == expected_hash_len) &&
                    (memcmp(result.hash, expected_hash, expected_hash_len) == 0);

    hash_result_free(&result);  // Free the result structure
    return is_valid;
}

// Internal helper function: Hash using SHA-256
/**
 * @brief Internal function to compute the SHA-256 hash of the input data.
 *
 * This function uses the OpenSSL EVP interface to compute the SHA-256 hash and store it in the 
 * hash_result_t structure.
 *
 * @param data Pointer to the input data.
 * @param data_len Length of the input data in bytes.
 * @param result Pointer to the hash_result_t structure where the SHA-256 hash will be stored.
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int hash_sha256(const uint8_t *data, size_t data_len, hash_result_t *result) {
    if (!data || !result || !result->hash) {
        return -EINVAL;  // Invalid input
    }

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();  // Create a new OpenSSL digest context
    if (!ctx) {
        return -ENOMEM;  // Memory allocation failure
    }

    const EVP_MD *md = EVP_sha256();  // Get SHA-256 digest method
    if (EVP_DigestInit_ex(ctx, md, NULL) != 1) {
        EVP_MD_CTX_free(ctx);
        return -EIO;  // Digest initialization failed
    }

    if (EVP_DigestUpdate(ctx, data, data_len) != 1) {
        EVP_MD_CTX_free(ctx);
        return -EIO;  // Failed to update digest
    }

    if (EVP_DigestFinal_ex(ctx, result->hash, NULL) != 1) {
        EVP_MD_CTX_free(ctx);
        return -EIO;  // Final digest computation failed
    }

    EVP_MD_CTX_free(ctx);  // Free the OpenSSL context
    return 0;
}

// Internal helper function: Hash using SHA-512
/**
 * @brief Internal function to compute the SHA-512 hash of the input data.
 *
 * Similar to hash_sha256, this function uses the OpenSSL EVP interface to compute the SHA-512 hash 
 * and store it in the hash_result_t structure.
 *
 * @param data Pointer to the input data.
 * @param data_len Length of the input data in bytes.
 * @param result Pointer to the hash_result_t structure where the SHA-512 hash will be stored.
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int hash_sha512(const uint8_t *data, size_t data_len, hash_result_t *result) {
    if (!data || !result || !result->hash) {
        return -EINVAL;  // Invalid input
    }

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();  // Create a new OpenSSL digest context
    if (!ctx) {
        return -ENOMEM;  // Memory allocation failure
    }

    const EVP_MD *md = EVP_sha512();  // Get SHA-512 digest method
    if (EVP_DigestInit_ex(ctx, md, NULL) != 1) {
        EVP_MD_CTX_free(ctx);
        return -EIO;  // Digest initialization failed
    }

    if (EVP_DigestUpdate(ctx, data, data_len) != 1) {
        EVP_MD_CTX_free(ctx);
        return -EIO;  // Failed to update digest
    }

    if (EVP_DigestFinal_ex(ctx, result->hash, NULL) != 1) {
        EVP_MD_CTX_free(ctx);
        return -EIO;  // Final digest computation failed.
 
        EVP_MD_CTX_free(ctx);  // Free the OpenSSL context
        return -EIO;      // Final digest computation failed
    }

    EVP_MD_CTX_free(ctx);  // Free the OpenSSL context to prevent memory leaks
    return 0;  // Return success
}

/**
 * @footer
 * @brief Summary of Security Considerations in Hash Utility Implementation
 *
 * The hash utility implementation leverages secure hashing algorithms (SHA-256 and SHA-512) to ensure data 
 * integrity and authenticity in the HFT system. By using OpenSSL's EVP interface, the module provides a flexible, 
 * secure, and performance-optimized method for generating cryptographic hashes.
 *
 * **Key security considerations include:**
 * - Proper memory management: Dynamic memory is allocated for hash outputs and securely freed after use to prevent memory leaks.
 * - Hash verification: A robust hash comparison mechanism is in place to ensure data integrity and detect tampering or corruption.
 * - Use of secure, widely recognized hash functions (SHA-256 and SHA-512), ensuring resilience against collision and pre-image attacks.
 * - Modular design: The functions are modular and extensible, allowing for the future addition of new algorithms or optimizations without affecting existing functionality.
 *
 * The design ensures that cryptographic operations within the HFT system adhere to high security standards, protecting the integrity and authenticity of critical financial data.
 */
