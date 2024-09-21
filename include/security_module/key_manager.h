/**
 * @file key_manager.h
 * @brief Security Module: Key Management Functions
 *
 * This header defines the key management operations within the security module of the HFT system. 
 * The module is responsible for securely handling cryptographic keys, including their generation, 
 * loading, saving, and rotation. Keys are critical assets in a cryptographic system, and their proper 
 * management is essential for ensuring data confidentiality and integrity.
 *
 * The supported key types include:
 * - AES (Advanced Encryption Standard): Typically used for symmetric encryption.
 * - RSA (Rivest-Shamir-Adleman): Used for asymmetric encryption, primarily for public/private key operations.
 *
 * Each key type is managed in a structure that allows for secure storage, retrieval, and erasure of key material.
 * The module also includes facilities for securely erasing keys from memory to prevent any residual data leakage.
 */

#ifndef SECURITY_MODULE_KEY_MANAGER_H
#define SECURITY_MODULE_KEY_MANAGER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define key sizes in bytes for various cryptographic algorithms
#define KEY_MANAGER_AES_KEY_SIZE 32  // AES-256 key size (256-bit encryption key)
#define KEY_MANAGER_RSA_KEY_SIZE 256 // RSA-2048 key size (2048-bit public key)
#define KEY_MANAGER_MAX_KEY_SIZE 256 // Max size for any key type, allowing future flexibility

// Enum to represent different key types
typedef enum {
    KEY_TYPE_AES,  // AES key type for symmetric encryption
    KEY_TYPE_RSA,  // RSA key type for asymmetric encryption
} key_type_t;

// Structure to represent a cryptographic key
typedef struct {
    key_type_t type;     // Specifies the type of the key (AES or RSA)
    uint8_t *key_data;   // Pointer to the raw bytes of the key material
    size_t key_length;   // Length of the key data in bytes
} crypto_key_t;

/**
 * @brief Initializes a key structure for the specified type.
 * 
 * This function allocates memory for a cryptographic key based on the key type and length. 
 * It is essential to call this function before performing any operations on a key to ensure 
 * the structure is properly initialized and memory is securely allocated.
 * 
 * @param key Pointer to the crypto_key_t structure to initialize.
 * @param type The type of cryptographic key (AES, RSA, etc.).
 * @param custom_length Custom key length (optional for flexibility, though default lengths are recommended).
 * @return int Returns 0 on success, or an error code if memory allocation fails.
 */
int key_init(crypto_key_t *key, key_type_t type, size_t custom_length);

/**
 * @brief Frees the memory associated with the key structure.
 * 
 * This function securely releases memory associated with a key, ensuring that sensitive data 
 * is properly erased from memory before deallocation to prevent residual leakage.
 *
 * @param key Pointer to the crypto_key_t structure to free.
 */
void key_free(crypto_key_t *key);

/**
 * @brief Generates a random cryptographic key.
 * 
 * This function generates a random key based on the specified key type (AES or RSA). For AES, 
 * it generates a 256-bit random key. For RSA, it generates a 2048-bit public/private key pair. 
 * The randomness of the generated key ensures strong cryptographic security.
 *
 * @param key Pointer to the crypto_key_t structure where the generated key will be stored.
 * @return int Returns 0 on success, or an error code if key generation fails.
 */
int key_generate_random(crypto_key_t *key);

/**
 * @brief Loads a key from a file.
 * 
 * This function reads a cryptographic key from a specified file. It is important to securely 
 * manage key files, as exposure of key material can compromise the entire system's security.
 *
 * @param key Pointer to the crypto_key_t structure where the loaded key will be stored.
 * @param file_path Path to the file containing the key.
 * @return int Returns 0 on success, or an error code if file operations fail.
 */
int key_load_from_file(crypto_key_t *key, const char *file_path);

/**
 * @brief Saves a key to a file.
 * 
 * This function saves a cryptographic key to a specified file. Files should be stored securely 
 * to prevent unauthorized access to key material, such as by using file encryption or secure storage locations.
 *
 * @param key Pointer to the crypto_key_t structure containing the key to save.
 * @param file_path Path to the file where the key will be saved.
 * @return int Returns 0 on success, or an error code if file operations fail.
 */
int key_save_to_file(const crypto_key_t *key, const char *file_path);

/**
 * @brief Rotates an existing key.
 * 
 * This function replaces the existing cryptographic key with a new one, ensuring continued 
 * security. Key rotation is an essential practice to mitigate risks of key compromise and 
 * limit the lifetime of any given key.
 *
 * @param key Pointer to the crypto_key_t structure containing the key to rotate.
 * @return int Returns 0 on success, or an error code if key rotation fails.
 */
int key_rotate(crypto_key_t *key);

/**
 * @brief Securely erase a key from memory.
 * 
 * This internal helper function ensures that sensitive key material is wiped from memory 
 * before the memory is released. This prevents key data from being recovered later by 
 * unauthorized parties or through memory forensic analysis.
 *
 * @param key Pointer to the crypto_key_t structure whose memory will be erased.
 */
void key_secure_erase(crypto_key_t *key);

#endif // SECURITY_MODULE_KEY_MANAGER_H

/**
 * @footer
 * @brief Summary of Key Management Security Considerations
 *
 * The key manager module provides essential functionality for securely handling cryptographic keys 
 * in the HFT system. All operations, from key initialization to secure erasure, are designed to minimize 
 * the risk of key compromise. This module strictly adheres to cryptographic best practices, including:
 * - Secure random generation of keys to ensure strong cryptographic resilience.
 * - Key rotation to regularly refresh keys and limit exposure in case of a breach.
 * - Secure erasure of keys from memory to avoid leaving sensitive data accessible after use.
 *
 * The use of established cryptographic standards such as AES-256 and RSA-2048 ensures that the module 
 * remains both performant and secure. The modular design allows for future expansion, including the integration 
 * of additional cryptographic algorithms as needed by evolving security requirements.
 */
