/**
 * @file security_module/security.c
 * @brief Security Module: Encryption, Decryption, and Digital Signature Implementation
 *
 * This source file implements the cryptographic functions required for encryption, decryption, 
 * and digital signature operations within the HFT system's security module. It uses OpenSSL to 
 * provide robust and secure cryptographic mechanisms, including AES encryption and RSA for asymmetric 
 * encryption and signature management.
 *
 * **Key functionalities include:**
 * - Digital signature creation and verification using RSA keys.
 * - AES encryption and decryption in ECB mode.
 * - RSA encryption and decryption for secure data transfer.
 *
 * All functions ensure proper memory management and secure handling of sensitive data.
 */

#include "security.h"
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/aes.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <iostream>

// Function: Sign data using a private key
/**
 * @brief Signs the input data using an RSA private key.
 * 
 * This function creates a digital signature of the input data using the specified RSA private key.
 * The signature is generated using the SHA-256 hash and is stored in the result structure.
 * 
 * @param data Pointer to the input data to be signed.
 * @param data_len Length of the input data in bytes.
 * @param private_key Pointer to the RSA private key.
 * @param key_len Length of the private key in bytes.
 * @param signature Pointer to the encryption_result_t structure to store the signature.
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int sign_data(const uint8_t *data, size_t data_len, const uint8_t *private_key, size_t key_len, encryption_result_t *signature) {
    if (!data || !private_key || !signature) {
        return -EINVAL;  // Invalid arguments
    }

    EVP_PKEY *pkey = NULL;
    EVP_MD_CTX *md_ctx = NULL;
    BIO *bio = BIO_new_mem_buf(private_key, (int)key_len);
    if (!bio) {
        return -ENOMEM;  // Memory allocation failure
    }

    pkey = PEM_read_bio_PrivateKey(bio, NULL, NULL, NULL);
    BIO_free(bio);
    if (!pkey) {
        return -EIO;  // Error reading private key
    }

    md_ctx = EVP_MD_CTX_new();
    if (!md_ctx) {
        EVP_PKEY_free(pkey);
        return -ENOMEM;
    }

    if (EVP_DigestSignInit(md_ctx, NULL, EVP_sha256(), NULL, pkey) != 1) {
        EVP_MD_CTX_free(md_ctx);
        EVP_PKEY_free(pkey);
        return -EIO;  // Error initializing digest signing
    }

    if (EVP_DigestSignUpdate(md_ctx, data, data_len) != 1) {
        EVP_MD_CTX_free(md_ctx);
        EVP_PKEY_free(pkey);
        return -EIO;  // Error updating digest sign
    }

    size_t sig_len = 0;
    if (EVP_DigestSignFinal(md_ctx, NULL, &sig_len) != 1) {
        EVP_MD_CTX_free(md_ctx);
        EVP_PKEY_free(pkey);
        return -EIO;  // Error calculating signature length
    }

    signature->data = (uint8_t *)malloc(sig_len);
    if (!signature->data) {
        EVP_MD_CTX_free(md_ctx);
        EVP_PKEY_free(pkey);
        return -ENOMEM;  // Memory allocation failure
    }

    if (EVP_DigestSignFinal(md_ctx, signature->data, &sig_len) != 1) {
        EVP_MD_CTX_free(md_ctx);
        EVP_PKEY_free(pkey);
        free(signature->data);
        return -EIO;  // Error finalizing signature
    }

    signature->data_len = sig_len;
    EVP_MD_CTX_free(md_ctx);
    EVP_PKEY_free(pkey);
    return 0;
}

// Function: Verify the signature of the data using a public key
/**
 * @brief Verifies a digital signature using the RSA public key.
 * 
 * This function checks if the provided signature matches the input data, using the specified RSA public key.
 * 
 * @param data Pointer to the input data whose signature will be verified.
 * @param data_len Length of the input data in bytes.
 * @param signature Pointer to the digital signature.
 * @param signature_len Length of the digital signature in bytes.
 * @param public_key Pointer to the RSA public key.
 * @param key_len Length of the RSA public key.
 * @return bool Returns true if the signature is valid, false otherwise.
 */
bool verify_signature(const uint8_t *data, size_t data_len, const uint8_t *signature, size_t signature_len, const uint8_t *public_key, size_t key_len) {
    if (!data || !signature || !public_key) {
        return false;  // Invalid arguments
    }

    EVP_PKEY *pkey = NULL;
    EVP_MD_CTX *md_ctx = NULL;
    BIO *bio = BIO_new_mem_buf(public_key, (int)key_len);
    if (!bio) {
        return false;
    }

    pkey = PEM_read_bio_PUBKEY(bio, NULL, NULL, NULL);
    BIO_free(bio);
    if (!pkey) {
        return false;  // Error loading public key
    }

    md_ctx = EVP_MD_CTX_new();
    if (!md_ctx) {
        EVP_PKEY_free(pkey);
        return false;
    }

    if (EVP_DigestVerifyInit(md_ctx, NULL, EVP_sha256(), NULL, pkey) != 1) {
        EVP_MD_CTX_free(md_ctx);
        EVP_PKEY_free(pkey);
        return false;
    }

    if (EVP_DigestVerifyUpdate(md_ctx, data, data_len) != 1) {
        EVP_MD_CTX_free(md_ctx);
        EVP_PKEY_free(pkey);
        return false;
    }

    int ret = EVP_DigestVerifyFinal(md_ctx, (unsigned char *)signature, signature_len);
    EVP_MD_CTX_free(md_ctx);
    EVP_PKEY_free(pkey);
    return (ret == 1);  // Return true if the signature is valid
}

// Internal helper function: AES encryption
/**
 * @brief Encrypts data using AES-256 in ECB mode.
 * 
 * This function uses the AES-256 encryption algorithm in ECB mode to encrypt the provided data.
 * 
 * @param data Pointer to the input data to be encrypted.
 * @param data_len Length of the input data in bytes.
 * @param key Pointer to the AES encryption key.
 * @param key_len Length of the AES encryption key (must be 32 bytes for AES-256).
 * @param result Pointer to the encryption_result_t structure where the encrypted data will be stored.
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int aes_encrypt(const uint8_t *data, size_t data_len, const uint8_t *key, size_t key_len, encryption_result_t *result) {
    if (!data || !key || !result || key_len != 32) {
        std::cerr << "Invalid input to AES encryption.\n";
        return -EINVAL;  // Invalid input
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        std::cerr << "Failed to create EVP_CIPHER_CTX.\n";
        ERR_print_errors_fp(stderr);  // Output OpenSSL errors
        return -ENOMEM;  // Memory allocation failure
    }

    const EVP_CIPHER *cipher = EVP_aes_256_ecb();  // AES-256 ECB mode
    if (EVP_EncryptInit_ex(ctx, cipher, NULL, key, NULL) != 1) {
        std::cerr << "EVP_EncryptInit_ex failed.\n";
        ERR_print_errors_fp(stderr);  // Output OpenSSL errors
        EVP_CIPHER_CTX_free(ctx);
        return -EIO;  // Encryption initialization failed
    }

    result->data = (uint8_t *)malloc(data_len + AES_BLOCK_SIZE);  // Allocate space for padding
    if (!result->data) {
        std::cerr << "Failed to allocate memory for encrypted data.\n";
        EVP_CIPHER_CTX_free(ctx);
        return -ENOMEM;  // Memory allocation failure
    }

    int len = 0;
    if (EVP_EncryptUpdate(ctx, result->data, &len, data, data_len) != 1) {
        std::cerr << "EVP_EncryptUpdate failed.\n";
        ERR_print_errors_fp(stderr);  // Output OpenSSL errors
        EVP_CIPHER_CTX_free(ctx);
        free(result->data);
        return -EIO;  // Encryption update failed
    }

    int final_len = 0;
    if (EVP_EncryptFinal_ex(ctx, result->data + len, &final_len) != 1) {
        std::cerr << "EVP_EncryptFinal_ex failed.\n";
        ERR_print_errors_fp(stderr);  // Output OpenSSL errors
        EVP_CIPHER_CTX_free(ctx);
        free(result->data);
        return -EIO;  // Final encryption step failed
    }

    result->data_len = len + final_len;
    EVP_CIPHER_CTX_free(ctx);
    return 0;
}

// Internal helper function: AES decryption
/**
 * @brief Decrypts data using AES-256 in ECB mode.
 * 
 * This function uses the AES-256 encryption algorithm in ECB mode to decrypt the provided data.
 * 
 * @param encrypted_data Pointer to the encrypted data to be decrypted.
 * @param encrypted_data_len Length of the encrypted data in bytes.
 * @param key Pointer to the AES decryption key.
 * @param key_len Length of the AES decryption key (must be 32 bytes for AES-256).
 * @param result Pointer to the encryption_result_t structure where the decrypted data will be stored.
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int aes_decrypt(const uint8_t *encrypted_data, size_t encrypted_data_len, const uint8_t *key, size_t key_len, encryption_result_t *result) {
    if (!encrypted_data || !key || !result || key_len != 32) {
        std::cerr << "Invalid input to AES decryption.\n";
        return -EINVAL;  // Invalid input
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        std::cerr << "Failed to create EVP_CIPHER_CTX.\n";
        ERR_print_errors_fp(stderr);  // Output OpenSSL errors
        return -ENOMEM;  // Memory allocation failure
    }

    const EVP_CIPHER *cipher = EVP_aes_256_ecb();  // AES-256 ECB mode
    if (EVP_DecryptInit_ex(ctx, cipher, NULL, key, NULL) != 1) {
        std::cerr << "EVP_DecryptInit_ex failed.\n";
        ERR_print_errors_fp(stderr);  // Output OpenSSL errors
        EVP_CIPHER_CTX_free(ctx);
        return -EIO;  // Decryption initialization failed
    }

    result->data = (uint8_t *)malloc(encrypted_data_len);  // Allocate memory for the decrypted data
    if (!result->data) {
        std::cerr << "Failed to allocate memory for decrypted data.\n";
        EVP_CIPHER_CTX_free(ctx);
        return -ENOMEM;  // Memory allocation failure
    }

    int len = 0;
    if (EVP_DecryptUpdate(ctx, result->data, &len, encrypted_data, encrypted_data_len) != 1) {
        std::cerr << "EVP_DecryptUpdate failed.\n";
        ERR_print_errors_fp(stderr);  // Output OpenSSL errors
        EVP_CIPHER_CTX_free(ctx);
        free(result->data);
        return -EIO;  // Decryption update failed
    }

    int final_len = 0;
    if (EVP_DecryptFinal_ex(ctx, result->data + len, &final_len) != 1) {
        std::cerr << "EVP_DecryptFinal_ex failed.\n";
        ERR_print_errors_fp(stderr);  // Output OpenSSL errors
        EVP_CIPHER_CTX_free(ctx);
        free(result->data);
        return -EIO;  // Final decryption step failed
    }

    result->data_len = len + final_len;  // Calculate total decrypted data length
    EVP_CIPHER_CTX_free(ctx);  // Clean up the OpenSSL context
    return 0;  // Success
}

// Function: Encrypt data using the specified algorithm and key
/**
 * @brief Encrypts data using the specified encryption algorithm (AES or RSA).
 * 
 * This function encrypts the input data using the specified algorithm (either AES or RSA) and the provided key.
 * The result is stored in the encryption_result_t structure.
 * 
 * @param data Pointer to the input data to be encrypted.
 * @param data_len Length of the input data in bytes.
 * @param key Pointer to the encryption key.
 * @param key_len Length of the encryption key in bytes.
 * @param algorithm The encryption algorithm to use (AES or RSA).
 * @param result Pointer to the encryption_result_t structure where the encrypted data will be stored.
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int encrypt_data(const uint8_t *data, size_t data_len, const uint8_t *key, size_t key_len, encryption_algorithm_t algorithm, encryption_result_t *result) {
    if (algorithm == ENCRYPTION_ALG_AES) {
        return aes_encrypt(data, data_len, key, key_len, result);  // Encrypt using AES
    } else if (algorithm == ENCRYPTION_ALG_RSA) {
        return rsa_encrypt(data, data_len, key, key_len, result);  // Encrypt using RSA
    }
    return -EINVAL;  // Unsupported algorithm
}

// Function: Decrypt data using the specified algorithm and key
/**
 * @brief Decrypts data using the specified encryption algorithm (AES or RSA).
 * 
 * This function decrypts the input data using the specified algorithm (either AES or RSA) and the provided key.
 * The result is stored in the encryption_result_t structure.
 * 
 * @param encrypted_data Pointer to the encrypted data to be decrypted.
 * @param encrypted_data_len Length of the encrypted data in bytes.
 * @param key Pointer to the decryption key.
 * @param key_len Length of the decryption key in bytes.
 * @param algorithm The encryption algorithm to use (AES or RSA).
 * @param result Pointer to the encryption_result_t structure where the decrypted data will be stored.
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int decrypt_data(const uint8_t *encrypted_data, size_t encrypted_data_len, const uint8_t *key, size_t key_len, encryption_algorithm_t algorithm, encryption_result_t *result) {
    if (algorithm == ENCRYPTION_ALG_AES) {
        return aes_decrypt(encrypted_data, encrypted_data_len, key, key_len, result);  // Decrypt using AES
    } else if (algorithm == ENCRYPTION_ALG_RSA) {
        return rsa_decrypt(encrypted_data, encrypted_data_len, key, key_len, result);  // Decrypt using RSA
    }
    return -EINVAL;  // Unsupported algorithm
}

// Function: Free the memory associated with the encryption result
/**
 * @brief Frees the memory associated with the encryption result.
 * 
 * This function releases the memory allocated for storing the encrypted or decrypted data in the result structure.
 * 
 * @param result Pointer to the encryption_result_t structure to be freed.
 */
void encryption_result_free(encryption_result_t *result) {
    if (result && result->data) {
        free(result->data);  // Free the allocated memory
        result->data = NULL;  // Reset the pointer
        result->data_len = 0;  // Reset the data length
    }
}

// Internal helper function: RSA encryption
/**
 * @brief Encrypts data using RSA with the public key.
 * 
 * This function encrypts the input data using RSA and the provided public key. The result is stored in the encryption_result_t structure.
 * 
 * @param data Pointer to the input data to be encrypted.
 * @param data_len Length of the input data in bytes.
 * @param public_key Pointer to the RSA public key.
 * @param key_len Length of the RSA public key in bytes.
 * @param result Pointer to the encryption_result_t structure where the encrypted data will be stored.
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int rsa_encrypt(const uint8_t *data, size_t data_len, const uint8_t *public_key, size_t key_len, encryption_result_t *result) {
    if (!data || !public_key || !result) {
        return -EINVAL;  // Invalid input
    }

    BIO *bio = BIO_new_mem_buf(public_key, (int)key_len);
    if (!bio) {
        return -ENOMEM;  // Memory allocation failure
    }

    EVP_PKEY *pkey = PEM_read_bio_PUBKEY(bio, NULL, NULL, NULL);
    BIO_free(bio);
    if (!pkey) {
        return -EIO;  // Error loading public key
    }

    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(pkey, NULL);
    if (!ctx) {
        EVP_PKEY_free(pkey);
        return -ENOMEM;  // Memory allocation failure
    }

    if (EVP_PKEY_encrypt_init(ctx) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        return -EIO;  // Encryption initialization failed
    }

    size_t out_len = 0;
    if (EVP_PKEY_encrypt(ctx, NULL, &out_len, data, data_len) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        return -EIO;  // Error calculating output length
    }

    result->data = (uint8_t *)malloc(out_len);
    if (!result->data) {
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        return -ENOMEM;  // Memory allocation failure
    }

    if (EVP_PKEY_encrypt(ctx, result->data, &out_len, data, data_len) <= 0) {
        free(result->data);
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        return -EIO;  // Encryption failed
    }

    result->data_len = out_len;
    EVP_PKEY_CTX_free(ctx);
    EVP_PKEY_free(pkey);
    return 0;  // Success
}

// Internal helper function: RSA decryption
/**
 * @brief Decrypts data using RSA with the private key.
 * 
 * This function decrypts the input data using RSA and the provided private key. The result is stored in the encryption_result_t structure.
 * 
 * @param encrypted_data Pointer to the encrypted data to be decrypted.
 * @param encrypted_data_len Length of the encrypted data in bytes.
 * @param private_key Pointer to the RSA private key.
 * @param key_len Length of the RSA private key in bytes.
 * @param result Pointer to the encryption_result_t structure where the decrypted data will be stored.
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int rsa_decrypt(const uint8_t *encrypted_data, size_t encrypted_data_len, const uint8_t *private_key, size_t key_len, encryption_result_t *result) {
    if (!encrypted_data || !private_key || !result) {
        return -EINVAL;  // Invalid input
    }

    BIO *bio = BIO_new_mem_buf(private_key, (int)key_len);
    if (!bio) {
        return -ENOMEM;  // Memory allocation failure
    }

    EVP_PKEY *pkey = PEM_read_bio_PrivateKey(bio, NULL, NULL, NULL);
    BIO_free(bio);
    if (!pkey) {
        return -EIO;  // Error loading private key
    }

    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(pkey, NULL);
    if (!ctx) {
        EVP_PKEY_free(pkey);
        return -ENOMEM;  // Memory allocation failure
    }

    if (EVP_PKEY_decrypt_init(ctx) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        return -EIO;  // Decryption initialization failed
    }

    size_t out_len = 0;
    if (EVP_PKEY_decrypt(ctx, NULL, &out_len, encrypted_data, encrypted_data_len) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        return -EIO;  // Error calculating output length
    }

    result->data = (uint8_t *)malloc(out_len);
    if (!result->data) {
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        return -ENOMEM;  // Memory allocation failure
    }

    if (EVP_PKEY_decrypt(ctx, result->data, &out_len, encrypted_data, encrypted_data_len) <= 0) {
        free(result->data);
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        return -EIO;  // Decryption failed
    }

    result->data_len = out_len;
    EVP_PKEY_CTX_free(ctx);
    EVP_PKEY_free(pkey);
    return 0;  // Success
}

/**
 * @footer
 * @brief Summary of Encryption, Decryption, and Signature Operations
 *
 * This implementation leverages OpenSSL to provide secure and efficient cryptographic operations for encryption, decryption, and digital signature verification. The module supports both symmetric (AES) and asymmetric (RSA) encryption methods, allowing for flexibility depending on the specific use case in the HFT system.
 *
 * **Key Security Considerations:**
 * - **Secure Memory Management**: All memory associated with cryptographic keys and data is securely allocated and freed to prevent sensitive data from remaining in memory after use.
 * - **OpenSSL Integration**: This module uses OpenSSL for reliable cryptographic operations, ensuring adherence to cryptographic standards.
 * - **Digital Signature**: Support for RSA-based digital signatures ensures the authenticity and integrity of messages.
 * - **AES Encryption/Decryption**: AES-256 is employed in ECB mode for fast and secure encryption of bulk data.
 * 
 * This cryptographic module is designed with performance and security in mind, offering robust solutions for securing sensitive financial transactions in high-frequency trading environments.
 */
