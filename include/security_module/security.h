/**
 * @file security.h
 * @brief Security Module: Encryption, Decryption, and Digital Signature Operations
 *
 * This header file defines the core cryptographic operations for the security module in the HFT system, 
 * including data encryption, decryption, and digital signatures. The supported cryptographic algorithms 
 * are AES (symmetric encryption) and RSA (asymmetric encryption), both of which are industry-standard 
 * for ensuring data confidentiality, integrity, and authenticity.
 *
 * Key features of this module include:
 * - **AES Encryption/Decryption**: Used for fast and secure symmetric key encryption, particularly useful for bulk data encryption.
 * - **RSA Encryption/Decryption**: Applied for asymmetric encryption, typically for secure key exchange and digital signatures.
 * - **Digital Signature Creation and Verification**: Provides mechanisms for creating and verifying digital signatures using RSA keys.
 *
 * All functions are designed with security in mind, ensuring that cryptographic materials are handled properly and securely erased when no longer needed.
 */

#ifndef SECURITY_MODULE_SECURITY_H
#define SECURITY_MODULE_SECURITY_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

// Define block sizes for encryption algorithms
#define SECURITY_AES_BLOCK_SIZE 16   // Block size for AES encryption (128-bit blocks)
#define SECURITY_RSA_BLOCK_SIZE 256  // Block size for RSA encryption (2048-bit keys)

// Enum to represent encryption algorithm types
typedef enum {
    ENCRYPTION_ALG_AES,  // AES encryption algorithm for symmetric key encryption
    ENCRYPTION_ALG_RSA   // RSA encryption algorithm for public/private key encryption
} encryption_algorithm_t;

// Structure to hold encryption/decryption result
typedef struct {
    uint8_t *data;     // Pointer to the encrypted or decrypted data
    size_t data_len;   // Length of the resulting data (in bytes)
} encryption_result_t;

/**
 * @brief Initializes the encryption result structure.
 * 
 * This function allocates memory for the output buffer where encrypted or decrypted data will be stored. 
 * It ensures the structure is ready for use by encryption or decryption functions.
 *
 * @param result Pointer to the encryption_result_t structure where the result will be stored.
 * @param data_len The length of the output data in bytes (determined by the encryption operation).
 * @return int Returns 0 on successful allocation, or a negative error code on failure (e.g., ENOMEM).
 */
int encryption_result_init(encryption_result_t *result, size_t data_len);

/**
 * @brief Frees the memory associated with the encryption result.
 * 
 * This function should be called once the encryption or decryption result is no longer needed to free 
 * the memory and prevent any potential memory leaks. It also ensures that sensitive data is properly 
 * erased before memory deallocation.
 *
 * @param result Pointer to the encryption_result_t structure whose memory will be freed.
 */
void encryption_result_free(encryption_result_t *result);

/**
 * @brief Encrypts data using the specified algorithm and key.
 * 
 * This function encrypts the input data using either the AES or RSA algorithm, depending on the provided 
 * key and algorithm type. The result is stored in the encryption_result_t structure.
 *
 * @param data Pointer to the input data to be encrypted.
 * @param data_len Length of the input data in bytes.
 * @param key Pointer to the key used for encryption (AES or RSA key).
 * @param key_len Length of the key in bytes (e.g., 32 bytes for AES-256, 256 bytes for RSA-2048).
 * @param algorithm Specifies whether AES or RSA encryption is used.
 * @param result Pointer to the encryption_result_t structure to store the encrypted data.
 * @return int Returns 0 on success, or a negative error code on failure (e.g., unsupported algorithm).
 */
int encrypt_data(const uint8_t *data, size_t data_len, const uint8_t *key, size_t key_len, encryption_algorithm_t algorithm, encryption_result_t *result);

/**
 * @brief Decrypts data using the specified algorithm and key.
 * 
 * This function decrypts the input encrypted data using either the AES or RSA algorithm, depending on the key 
 * and algorithm type. The decrypted result is stored in the encryption_result_t structure.
 *
 * @param encrypted_data Pointer to the input data to be decrypted.
 * @param encrypted_data_len Length of the encrypted data in bytes.
 * @param key Pointer to the key used for decryption (AES or RSA key).
 * @param key_len Length of the key in bytes.
 * @param algorithm Specifies whether AES or RSA decryption is used.
 * @param result Pointer to the encryption_result_t structure to store the decrypted data.
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int decrypt_data(const uint8_t *encrypted_data, size_t encrypted_data_len, const uint8_t *key, size_t key_len, encryption_algorithm_t algorithm, encryption_result_t *result);

/**
 * @brief Signs data using a private key.
 * 
 * This function creates a digital signature for the input data using the provided RSA private key. 
 * The signature is stored in the encryption_result_t structure.
 *
 * @param data Pointer to the input data to be signed.
 * @param data_len Length of the input data in bytes.
 * @param private_key Pointer to the RSA private key.
 * @param key_len Length of the RSA private key in bytes.
 * @param signature Pointer to the encryption_result_t structure to store the resulting signature.
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int sign_data(const uint8_t *data, size_t data_len, const uint8_t *private_key, size_t key_len, encryption_result_t *signature);

/**
 * @brief Verifies the signature of the data using a public key.
 * 
 * This function verifies the digital signature of the input data using the provided RSA public key. 
 * It checks whether the signature matches the data, ensuring data integrity and authenticity.
 *
 * @param data Pointer to the input data whose signature needs to be verified.
 * @param data_len Length of the input data in bytes.
 * @param signature Pointer to the signature to be verified.
 * @param signature_len Length of the signature in bytes.
 * @param public_key Pointer to the RSA public key used for verification.
 * @param key_len Length of the RSA public key in bytes.
 * @return bool Returns true if the signature is valid, false otherwise.
 */
bool verify_signature(const uint8_t *data, size_t data_len, const uint8_t *signature, size_t signature_len, const uint8_t *public_key, size_t key_len);

/**
 * @brief Internal helper function: AES encryption.
 * 
 * This is an internal function for AES encryption. It should be used only by the `encrypt_data` 
 * function when AES is the selected algorithm. It ensures the proper handling of AES-specific 
 * block size and key length requirements.
 *
 * @param data Pointer to the input data to be encrypted.
 * @param data_len Length of the input data in bytes.
 * @param key Pointer to the AES key.
 * @param key_len Length of the AES key (typically 32 bytes for AES-256).
 * @param result Pointer to the encryption_result_t structure to store the encrypted data.
 * @return int Returns 0 on success, or an error code on failure.
 */
int aes_encrypt(const uint8_t *data, size_t data_len, const uint8_t *key, size_t key_len, encryption_result_t *result);

/**
 * @brief Internal helper function: AES decryption.
 * 
 * This function performs AES decryption and is used internally within the module. It handles AES-specific 
 * operations and returns the decrypted data through the `encryption_result_t` structure.
 *
 * @param encrypted_data Pointer to the encrypted data.
 * @param encrypted_data_len Length of the encrypted data in bytes.
 * @param key Pointer to the AES key.
 * @param key_len Length of the AES key.
 * @param result Pointer to the encryption_result_t structure to store the decrypted data.
 * @return int Returns 0 on success, or an error code on failure.
 */
int aes_decrypt(const uint8_t *encrypted_data, size_t encrypted_data_len, const uint8_t *key, size_t key_len, encryption_result_t *result);

/**
 * @brief Internal helper function: RSA encryption.
 * 
 * This function performs RSA encryption. It is used internally by the `encrypt_data` function when RSA 
 * is the selected algorithm. It handles RSA-specific padding and key operations.
 *
 * @param data Pointer to the input data to be encrypted.
 * @param data_len Length of the input data.
 * @param public_key Pointer to the RSA public key.
 * @param key_len Length of the RSA public key.
 * @param result Pointer to the encryption_result_t structure to store the encrypted data.
 * @return int Returns 0 on success, or an error code on failure.
 */
int rsa_encrypt(const uint8_t *data, size_t data_len, const uint8_t *public_key, size_t key_len, encryption_result_t *result);

/**
 * @brief Internal helper function: RSA decryption.
 * 
 * This function performs RSA decryption, internally used by the `decrypt_data` function. It handles RSA-specific 
 * operations and returns the decrypted data through the `encryption_result_t` structure.
 *
 * @param encrypted_data Pointer to the encrypted data.
 * @param encrypted_data_len Length of the encrypted data.
 * @param private_key Pointer to the RSA private key.
 * @param key_len Length of the RSA private key.
 * @param result Pointer to the encryption_result_t structure to store the decrypted data.
 * @return int Returns 0 on success, or an error code on failure.
 */
int rsa_decrypt(const uint8_t *encrypted_data, size_t encrypted_data_len, const uint8_t *private_key, size_t key_len, encryption_result_t *result);

#endif // SECURITY_MODULE_SECURITY_H

/**
 * @footer
 * @brief Summary of Security and Cryptographic Considerations
 *
 * The security module provides robust cryptographic capabilities, ensuring both confidentiality and integrity 
 * for the data processed within the HFT system. By supporting both AES for fast symmetric encryption and RSA for 
 * secure asymmetric operations (e.g., key exchange, digital signatures), this module achieves a balance between 
 * performance and security.
 *
 * **Key security practices implemented in this module:**
 * - Proper initialization and secure deallocation of cryptographic materials to prevent memory leaks and residual data exposure.
 * - Use of industry-standard algorithms (AES-256, RSA-2048) to ensure cryptographic strength and resilience against attacks.
 * - Modular architecture allowing for the future extension of additional encryption and signature schemes.
 *
 * The use of secure key management practices (e.g., key rotation, secure key storage) is strongly recommended in conjunction with this module to maintain the overall security of the system.
 */
