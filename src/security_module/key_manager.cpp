/**
 * @file key_manager.c
 * @brief Security Module: Key Management Implementation
 *
 * This source file implements key management functionality for the HFT system's security module. 
 * The key manager is responsible for securely handling cryptographic keys, including generation, 
 * loading from file, saving to file, and key rotation. The module ensures that sensitive key data 
 * is securely erased from memory after use to prevent potential leaks or unauthorized access.
 *
 * **Key features include:**
 * - Secure random key generation using system sources (e.g., /dev/urandom).
 * - Key loading and saving with secure file I/O operations.
 * - Key rotation with secure erasure of the old key.
 * - Memory handling and secure erasure for cryptographic key data.
 */

#include "key_manager.h"
#include <fcntl.h>    // For file I/O (open, O_RDONLY, O_WRONLY)
#include <unistd.h>   // For file I/O (read, write, close)
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// Secure random number generation helper function
/**
 * @brief Generate secure random bytes using /dev/urandom.
 *
 * This function reads a specified number of random bytes from the system's secure random source 
 * (/dev/urandom) and stores them in the provided buffer.
 *
 * @param buffer Pointer to the buffer where the random bytes will be stored.
 * @param length The number of random bytes to generate.
 * @return int Returns 0 on success, or -EIO if there was an error reading from the random source.
 */
static int generate_secure_random_bytes(uint8_t *buffer, size_t length) {
    int fd = open("/dev/urandom", O_RDONLY);  // Open /dev/urandom for secure random bytes
    if (fd < 0) {
        return -EIO;  // Error opening the random source
    }

    ssize_t read_bytes = read(fd, buffer, length);  // Read random bytes into buffer
    close(fd);

    if (read_bytes != (ssize_t)length) {
        return -EIO;  // Error: did not read enough random bytes
    }

    return 0;  // Success
}

// Function: Initialize the key structure
/**
 * @brief Initializes the key structure for the specified key type.
 *
 * This function allocates memory for a cryptographic key, ensuring that it can hold the appropriate 
 * number of bytes based on the key type (AES or RSA). It also allows for custom key lengths.
 *
 * @param key Pointer to the crypto_key_t structure to initialize.
 * @param type The type of cryptographic key (AES or RSA).
 * @param custom_length Optional custom key length (0 to use default).
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int key_init(crypto_key_t *key, key_type_t type, size_t custom_length) {
    if (!key) {
        return -EINVAL;  // Invalid argument
    }

    key->type = type;  // Set the key type
    switch (type) {
        case KEY_TYPE_AES:
            key->key_length = custom_length > 0 ? custom_length : KEY_MANAGER_AES_KEY_SIZE;  // AES key length
            break;
        case KEY_TYPE_RSA:
            key->key_length = custom_length > 0 ? custom_length : KEY_MANAGER_RSA_KEY_SIZE;  // RSA key length
            break;
        default:
            return -EINVAL;  // Unsupported key type
    }

    key->key_data = (uint8_t *)malloc(key->key_length);  // Allocate memory for the key data
    if (!key->key_data) {
        return -ENOMEM;  // Memory allocation failed
    }

    return 0;  // Success
}

// Function: Free the memory associated with the key structure
/**
 * @brief Frees the memory associated with the key structure.
 *
 * This function securely erases the cryptographic key from memory before releasing it, preventing sensitive 
 * information from being left in memory after the key is no longer needed.
 *
 * @param key Pointer to the crypto_key_t structure to free.
 */
void key_free(crypto_key_t *key) {
    if (key && key->key_data) {
        key_secure_erase(key);  // Securely erase the key data before freeing memory
        free(key->key_data);  // Free the allocated memory
        key->key_data = NULL;  // Reset the key data pointer
        key->key_length = 0;  // Reset the key length
    }
}

// Function: Generate a random cryptographic key
/**
 * @brief Generates a random cryptographic key.
 *
 * This function fills the key's memory with securely generated random bytes, using the system's secure 
 * random number generator (/dev/urandom).
 *
 * @param key Pointer to the crypto_key_t structure where the key will be stored.
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int key_generate_random(crypto_key_t *key) {
    if (!key || !key->key_data) {
        return -EINVAL;  // Invalid key structure
    }

    return generate_secure_random_bytes(key->key_data, key->key_length);  // Generate random bytes for the key
}

// Function: Load a key from a file
/**
 * @brief Loads a cryptographic key from a file.
 *
 * This function reads a cryptographic key from the specified file and stores it in the key structure. 
 * The file should be securely protected to prevent unauthorized access to the key material.
 *
 * @param key Pointer to the crypto_key_t structure where the key will be loaded.
 * @param file_path Path to the file containing the key.
 * @return int Returns 0 on success, or a negative error code if the file could not be opened or read.
 */
int key_load_from_file(crypto_key_t *key, const char *file_path) {
    if (!key || !file_path) {
        return -EINVAL;  // Invalid arguments
    }

    int fd = open(file_path, O_RDONLY);  // Open the file for reading
    if (fd < 0) {
        return -ENOENT;  // File not found or cannot be opened
    }

    ssize_t read_bytes = read(fd, key->key_data, key->key_length);  // Read the key data from the file
    close(fd);

    if (read_bytes != (ssize_t)key->key_length) {
        return -EIO;  // Error: did not read the entire key
    }

    return 0;  // Success
}

// Function: Save a key to a file
/**
 * @brief Saves a cryptographic key to a file.
 *
 * This function writes the key data to the specified file. The file is created with secure permissions 
 * to protect the key from unauthorized access (only the file owner can read/write the key).
 *
 * @param key Pointer to the crypto_key_t structure containing the key to save.
 * @param file_path Path to the file where the key will be saved.
 * @return int Returns 0 on success, or a negative error code if the file could not be opened or written.
 */
int key_save_to_file(const crypto_key_t *key, const char *file_path) {
    if (!key || !file_path) {
        return -EINVAL;  // Invalid arguments
    }

    int fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0600);  // Open the file for writing with secure permissions
    if (fd < 0) {
        return -EACCES;  // File could not be opened for writing
    }

    ssize_t written_bytes = write(fd, key->key_data, key->key_length);  // Write the key data to the file
    close(fd);

    if (written_bytes != (ssize_t)key->key_length) {
        return -EIO;  // Error: did not write the entire key
    }

    return 0;  // Success
}

// Function: Rotate an existing key (generate a new key to replace the old one)
/**
 * @brief Rotates an existing cryptographic key by generating a new random key.
 *
 * This function securely erases the current key from memory and generates a new random key in its place, 
 * ensuring that the old key cannot be recovered after the rotation.
 *
 * @param key Pointer to the crypto_key_t structure containing the key to rotate.
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int key_rotate(crypto_key_t *key) {
    if (!key || !key->key_data) {
        return -EINVAL;  // Invalid key structure
    }

    // Securely erase the current key before generating a new one
    key_secure_erase(key);

    // Generate a new random key
    return key_generate_random(key);
}

// Internal helper function: Securely erase a key from memory
/**
 * @brief Securely erases a cryptographic key from memory.
 *
 * This function overwrites the key data with zeros to ensure that the sensitive key material is securely 
 * erased and cannot be recovered after it is no longer needed.
 *
 * @param key Pointer to the crypto_key_t structure containing the key to erase.
 */
void key_secure_erase(crypto_key_t *key) {
    if (key && key->key_data) {
        memset(key->key_data, 0, key->key_length);  // Overwrite key data with zeros
    }
}

/**
 * @footer
 * @brief Summary of Key Management Security Considerations
 *
 * The key management module in this implementation is designed to securely handle cryptographic keys throughout their lifecycle,
 * ensuring confidentiality and integrity within the HFT system. The design follows cryptographic best practices such as secure 
 * random key generation, secure file handling, and memory management. Key erasure mechanisms further ensure that sensitive 
 * information is not left in memory after a key is rotated or freed.
 *
 * **Key security considerations include:**
 * - **Secure random key generation**: Keys are generated using the system's secure random number generator (/dev/urandom), ensuring strong entropy.
 * - **Memory security**: Key data is securely erased from memory using `key_secure_erase` before deallocation, preventing any residual data leakage.
 * - **File security**: Keys are saved with strict file permissions (0600) to limit access to the file owner, mitigating unauthorized access risks.
 * - **Key rotation**: The key rotation mechanism ensures the old key is securely wiped before generating a new one, minimizing the risk of key exposure over time.
 * 
 * This module provides a flexible, extensible, and secure foundation for managing cryptographic keys within the system, with the ability to adapt to future security requirements.
 */
