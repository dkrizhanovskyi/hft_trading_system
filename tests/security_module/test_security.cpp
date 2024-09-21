#include <openssl/aes.h> 
#include <openssl/err.h>   
#include <openssl/rsa.h>  
#include <openssl/pem.h>  
#include <openssl/rand.h>
#include <openssl/bn.h>  
#include <iostream>
#include <cassert>
#include <cstring>
#include "security.h"

// Генерация случайных байтов
int generate_secure_random_bytes(uint8_t *buffer, size_t length) {
    if (RAND_bytes(buffer, length) != 1) {
        ERR_print_errors_fp(stderr);
        return -1;  // Ошибка генерации
    }
    return 0;
}

// Test case: AES encryption and decryption
void test_aes_encryption_decryption() {
    const char *plaintext = "Sensitive Data";
    const size_t plaintext_len = strlen(plaintext);

    // Generate a random AES-256 key (32 bytes)
    const size_t aes_key_size = 32;  // 256 бит для AES-256
    uint8_t aes_key[aes_key_size];
    int ret = generate_secure_random_bytes(aes_key, aes_key_size);
    assert(ret == 0);

    // Encrypt the plaintext
    encryption_result_t encrypted_result;
    ret = aes_encrypt((const uint8_t *)plaintext, plaintext_len, aes_key, aes_key_size, &encrypted_result);
    assert(ret == 0);
    std::cout << "AES encryption successful. Encrypted length: " << encrypted_result.data_len << std::endl;

    // Decrypt the ciphertext
    encryption_result_t decrypted_result;
    ret = aes_decrypt(encrypted_result.data, encrypted_result.data_len, aes_key, aes_key_size, &decrypted_result);
    if (ret != 0) {
        std::cerr << "AES decryption failed with error code: " << ret << std::endl;
        ERR_print_errors_fp(stderr);  // Вывод ошибок OpenSSL
    }
    assert(ret == 0);

    // Check that the decrypted text matches the original plaintext
    assert(decrypted_result.data_len == plaintext_len);
    assert(memcmp(decrypted_result.data, plaintext, plaintext_len) == 0);
    std::cout << "AES decryption successful. Decrypted text: " << (char *)decrypted_result.data << std::endl;

    // Clean up
    encryption_result_free(&encrypted_result);
    encryption_result_free(&decrypted_result);
}

// Helper function to create a temporary keypair (RSA)
void generate_rsa_keypair(uint8_t **private_key, size_t *private_key_len, uint8_t **public_key, size_t *public_key_len) {
    EVP_PKEY *pkey = EVP_PKEY_new();
    RSA *rsa = RSA_new();
    BIGNUM *bn = BN_new();
    if (!pkey || !rsa || !bn) {
        std::cerr << "Memory allocation failed for key generation." << std::endl;
        ERR_print_errors_fp(stderr);
        return;
    }

    BN_set_word(bn, RSA_F4);

    // Генерация ключа
    if (RSA_generate_key_ex(rsa, 2048, bn, NULL) != 1) {
        std::cerr << "RSA key generation failed." << std::endl;
        ERR_print_errors_fp(stderr);
        EVP_PKEY_free(pkey);
        RSA_free(rsa);
        BN_free(bn);
        return;
    }

    EVP_PKEY_assign_RSA(pkey, rsa);

    // Write the private key to a memory BIO
    BIO *priv_bio = BIO_new(BIO_s_mem());
    if (!priv_bio) {
        std::cerr << "BIO memory allocation failed." << std::endl;
        ERR_print_errors_fp(stderr);
        EVP_PKEY_free(pkey);
        return;
    }

    PEM_write_bio_PrivateKey(priv_bio, pkey, NULL, NULL, 0, NULL, NULL);
    *private_key_len = BIO_pending(priv_bio);
    *private_key = (uint8_t *)malloc(*private_key_len);
    BIO_read(priv_bio, *private_key, *private_key_len);
    BIO_free(priv_bio);

    // Write the public key to a memory BIO
    BIO *pub_bio = BIO_new(BIO_s_mem());
    if (!pub_bio) {
        std::cerr << "BIO memory allocation failed." << std::endl;
        ERR_print_errors_fp(stderr);
        EVP_PKEY_free(pkey);
        return;
    }

    PEM_write_bio_PUBKEY(pub_bio, pkey);
    *public_key_len = BIO_pending(pub_bio);
    *public_key = (uint8_t *)malloc(*public_key_len);
    BIO_read(pub_bio, *public_key, *public_key_len);
    BIO_free(pub_bio);

    EVP_PKEY_free(pkey);
    BN_free(bn);  // Освобождение ресурсов BIGNUM
}

// Test case: RSA signature and verification
void test_rsa_signature_verification() {
    const char *message = "Message to be signed";
    const size_t message_len = strlen(message);

    // Generate RSA key pair
    uint8_t *private_key = nullptr;
    size_t private_key_len = 0;
    uint8_t *public_key = nullptr;
    size_t public_key_len = 0;
    generate_rsa_keypair(&private_key, &private_key_len, &public_key, &public_key_len);

    // Sign the message
    encryption_result_t signature_result;
    int ret = sign_data((const uint8_t *)message, message_len, private_key, private_key_len, &signature_result);
    if (ret != 0) {
        std::cerr << "RSA signing failed with error code: " << ret << std::endl;
        ERR_print_errors_fp(stderr);  // Вывод ошибок OpenSSL
    }
    assert(ret == 0);
    std::cout << "RSA signature successful. Signature length: " << signature_result.data_len << std::endl;

    // Verify the signature
    bool is_valid = verify_signature((const uint8_t *)message, message_len, signature_result.data, signature_result.data_len, public_key, public_key_len);
    assert(is_valid);
    std::cout << "RSA signature verification successful." << std::endl;

    // Clean up
    free(private_key);
    free(public_key);
    encryption_result_free(&signature_result);
}

// Test case: RSA encryption and decryption
void test_rsa_encryption_decryption() {
    const char *message = "Sensitive message for RSA encryption";
    const size_t message_len = strlen(message);

    // Generate RSA key pair
    uint8_t *private_key = nullptr;
    size_t private_key_len = 0;
    uint8_t *public_key = nullptr;
    size_t public_key_len = 0;
    generate_rsa_keypair(&private_key, &private_key_len, &public_key, &public_key_len);

    // Encrypt the message
    encryption_result_t encrypted_result;
    int ret = rsa_encrypt((const uint8_t *)message, message_len, public_key, public_key_len, &encrypted_result);
    assert(ret == 0);
    std::cout << "RSA encryption successful. Encrypted length: " << encrypted_result.data_len << std::endl;

    // Decrypt the message
    encryption_result_t decrypted_result;
    ret = rsa_decrypt(encrypted_result.data, encrypted_result.data_len, private_key, private_key_len, &decrypted_result);
    assert(ret == 0);

    // Check that the decrypted message matches the original
    assert(decrypted_result.data_len == message_len);
    assert(memcmp(decrypted_result.data, message, message_len) == 0);
    std::cout << "RSA decryption successful. Decrypted message: " << (char *)decrypted_result.data << std::endl;

    // Clean up
    free(private_key);
    free(public_key);
    encryption_result_free(&encrypted_result);
    encryption_result_free(&decrypted_result);
}

// Main function to run all security module tests
int main() {
    test_aes_encryption_decryption();
    test_rsa_signature_verification();
    test_rsa_encryption_decryption();

    std::cout << "All security module tests passed!" << std::endl;
    return 0;
}
