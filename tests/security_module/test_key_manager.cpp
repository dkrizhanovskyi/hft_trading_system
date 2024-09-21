#include <iostream>
#include <cassert>
#include <cstring>
#include "key_manager.h"
#include <unistd.h>  // POSIX for file operations

// Helper function to create a temporary file
std::string create_temp_file() {
    char temp_file_template[] = "/tmp/test_key_manager_XXXXXX";
    int fd = mkstemp(temp_file_template);  // Create a temporary file and get its file descriptor
    if (fd == -1) {
        std::cerr << "Error creating temporary file" << std::endl;
        exit(EXIT_FAILURE);
    }
    close(fd);  // Close the file descriptor, we will only use the path for testing
    return std::string(temp_file_template);
}

// Test: Key initialization
void test_key_init() {
    crypto_key_t key;

    // Testing AES key initialization
    int ret = key_init(&key, KEY_TYPE_AES, 0);
    assert(ret == 0);
    assert(key.key_length == KEY_MANAGER_AES_KEY_SIZE);
    assert(key.key_data != nullptr);

    std::cout << "AES key initialization successful. Key length: " << key.key_length << std::endl;
    key_free(&key);

    // Testing RSA key initialization
    ret = key_init(&key, KEY_TYPE_RSA, 0);
    assert(ret == 0);
    assert(key.key_length == KEY_MANAGER_RSA_KEY_SIZE);
    assert(key.key_data != nullptr);

    std::cout << "RSA key initialization successful. Key length: " << key.key_length << std::endl;
    key_free(&key);
}

// Test: Random key generation
void test_key_generate_random() {
    crypto_key_t key;

    // Initialize AES key and generate random data
    int ret = key_init(&key, KEY_TYPE_AES, 0);
    assert(ret == 0);

    ret = key_generate_random(&key);
    assert(ret == 0);

    std::cout << "Random AES key generation successful. Key length: " << key.key_length << std::endl;
    key_free(&key);
}

// Test: Saving and loading key from a file
void test_key_save_and_load() {
    crypto_key_t key;

    // Initialize AES key and generate random data
    int ret = key_init(&key, KEY_TYPE_AES, 0);
    assert(ret == 0);

    ret = key_generate_random(&key);
    assert(ret == 0);

    // Create a temporary file for saving the key
    std::string temp_file = create_temp_file();

    // Save the key to the file
    ret = key_save_to_file(&key, temp_file.c_str());
    assert(ret == 0);
    std::cout << "AES key saved to file successfully: " << temp_file << std::endl;

    // Free the key before loading it back
    key_free(&key);

    // Initialize the key and load it from the file
    ret = key_init(&key, KEY_TYPE_AES, 0);
    assert(ret == 0);

    ret = key_load_from_file(&key, temp_file.c_str());
    assert(ret == 0);
    std::cout << "AES key loaded from file successfully: " << temp_file << std::endl;

    key_free(&key);

    // Delete the temporary file after the test
    unlink(temp_file.c_str());
}

// Test: Key rotation
void test_key_rotate() {
    crypto_key_t key;

    // Initialize AES key and generate random data
    int ret = key_init(&key, KEY_TYPE_AES, 0);
    assert(ret == 0);

    ret = key_generate_random(&key);
    assert(ret == 0);

    uint8_t *old_key_data = (uint8_t *)malloc(key.key_length);
    memcpy(old_key_data, key.key_data, key.key_length);

    // Rotate the key (generate a new key)
    ret = key_rotate(&key);
    assert(ret == 0);

    // Ensure that the key data has changed
    assert(memcmp(old_key_data, key.key_data, key.key_length) != 0);
    std::cout << "Key rotation successful." << std::endl;

    key_free(&key);
    free(old_key_data);
}

// Main function to run all tests
int main() {
    test_key_init();
    test_key_generate_random();
    test_key_save_and_load();
    test_key_rotate();

    std::cout << "All tests for the key manager passed successfully!" << std::endl;
    return 0;
}
