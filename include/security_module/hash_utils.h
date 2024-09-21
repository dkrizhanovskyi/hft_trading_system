/**
 * @file hash_utils.h
 * @brief Security Module: Hash Utility Functions
 *
 * This header file defines the core functions and structures for hash-based operations 
 * within the security module. The module is designed to support multiple hash algorithms, 
 * primarily SHA-256 and SHA-512, ensuring secure cryptographic hashing of data. These functions 
 * are integral to maintaining data integrity and verifying authenticity in the High-Frequency Trading (HFT) system.
 *
 * Key functionalities provided by this module include:
 * - Initialization of hash result structures
 * - Hashing of data using secure algorithms (SHA-256 and SHA-512)
 * - Verification of data integrity through hash comparison
 * - Safe allocation and deallocation of memory for hash outputs
 *
 * The module is designed with extensibility in mind, allowing for the addition of new hash algorithms in the future.
 * Cryptographic security is ensured by strictly following industry-standard hash algorithms and avoiding unsafe memory operations.
 */

#ifndef SECURITY_MODULE_HASH_UTILS_H
#define SECURITY_MODULE_HASH_UTILS_H

#include <stddef.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define a constant for the default hash size (SHA-256)
#define HASH_UTILS_SHA256_SIZE 32
// Defines the standard output length for SHA-256 hash algorithms (256 bits = 32 bytes).

// Enum to represent different hash algorithm types
typedef enum {
    HASH_ALG_SHA256,  // SHA-256 hashing algorithm, a widely-used, secure 256-bit hash function.
    HASH_ALG_SHA512   // SHA-512 hashing algorithm, a 512-bit variant providing stronger security.
} hash_algorithm_t;

// Structure to hold the result of a hash operation
typedef struct {
    uint8_t *hash;    // Pointer to the hash output, dynamically allocated based on algorithm.
    size_t hash_len;  // Length of the generated hash, determined by the algorithm used.
} hash_result_t;

/**
 * @brief Initializes the hash result structure.
 * 
 * This function allocates memory for the hash output buffer depending on the selected algorithm.
 * It is crucial to call this function before performing any hash operation to ensure proper memory allocation.
 *
 * @param result Pointer to the hash_result_t structure where the hash output will be stored.
 * @param algorithm Specifies which hash algorithm (SHA-256 or SHA-512) to use, determining the hash length.
 * @return int Returns 0 on successful allocation, or an error code (e.g., ENOMEM) if memory allocation fails.
 */
int hash_result_init(hash_result_t *result, hash_algorithm_t algorithm);

/**
 * @brief Frees memory associated with the hash result structure.
 * 
 * This function must be called once the hash result is no longer needed to avoid memory leaks. 
 * It ensures that dynamically allocated memory for the hash buffer is properly deallocated.
 *
 * @param result Pointer to the hash_result_t structure to be freed.
 */
void hash_result_free(hash_result_t *result);

/**
 * @brief Hash data using the selected algorithm.
 * 
 * This function takes a pointer to the input data, its size, and the selected hash algorithm, 
 * then computes the cryptographic hash and stores the result in the provided structure.
 * 
 * @param data Pointer to the input data to be hashed.
 * @param data_len Length of the input data in bytes.
 * @param algorithm Specifies which hash algorithm to use (SHA-256 or SHA-512).
 * @param result Pointer to the hash_result_t structure to store the resulting hash.
 * @return int Returns 0 on success, or an error code if hashing fails (e.g., due to memory issues or unsupported data).
 */
int hash_data(const uint8_t *data, size_t data_len, hash_algorithm_t algorithm, hash_result_t *result);

/**
 * @brief Verify if the given data matches the provided hash.
 * 
 * This function is used to check the integrity of data by comparing its computed hash with a provided expected hash.
 * It ensures that the data has not been tampered with or corrupted by verifying cryptographic consistency.
 *
 * @param data Pointer to the input data whose integrity needs to be verified.
 * @param data_len Length of the input data in bytes.
 * @param expected_hash Pointer to the expected hash value.
 * @param expected_hash_len Length of the expected hash value in bytes.
 * @param algorithm The hash algorithm (SHA-256 or SHA-512) used to generate the expected hash.
 * @return bool Returns true if the hashes match, indicating the data is intact, false otherwise.
 */
bool verify_hash(const uint8_t *data, size_t data_len, const uint8_t *expected_hash, size_t expected_hash_len, hash_algorithm_t algorithm);

/**
 * @brief Internal helper function: Hash using SHA-256.
 * 
 * This is an internal function used exclusively within the module to handle SHA-256-specific hashing operations.
 * It is not intended to be exposed to external modules.
 * 
 * @param data Pointer to the input data to be hashed.
 * @param data_len Length of the input data in bytes.
 * @param result Pointer to the hash_result_t structure to store the resulting hash.
 * @return int Returns 0 on success or an error code in case of failure.
 */
int hash_sha256(const uint8_t *data, size_t data_len, hash_result_t *result);

/**
 * @brief Internal helper function: Hash using SHA-512.
 * 
 * Similar to hash_sha256, this function handles SHA-512-specific hashing operations. 
 * It provides enhanced security with a longer hash output (512 bits).
 *
 * @param data Pointer to the input data to be hashed.
 * @param data_len Length of the input data in bytes.
 * @param result Pointer to the hash_result_t structure to store the resulting hash.
 * @return int Returns 0 on success or an error code in case of failure.
 */
int hash_sha512(const uint8_t *data, size_t data_len, hash_result_t *result);

#endif // SECURITY_MODULE_HASH_UTILS_H

/**
 * @footer
 * @brief Summary of Security and Architectural Considerations
 * 
 * The hash utility module is a crucial part of the HFT security infrastructure, ensuring data integrity and authenticity 
 * through reliable cryptographic hash functions. By supporting both SHA-256 and SHA-512 algorithms, the module provides 
 * flexibility between performance and security, allowing system architects to choose the appropriate level of cryptographic strength.
 *
 * Important security practices implemented in this module include:
 * - Strict memory management to prevent leaks or buffer overflows during hash operations.
 * - Use of industry-standard hash algorithms, following best practices for cryptographic strength and data protection.
 * - Extensibility for future integration of additional hash algorithms without affecting existing components.
 * 
 * All functions are designed to be modular, secure, and efficient, ensuring their seamless integration into the larger HFT system without compromising performance or security.
 */
