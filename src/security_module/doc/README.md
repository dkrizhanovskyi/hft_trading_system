# Security Module for High-Frequency Trading Systems

## Overview

The `security_module` is a cryptographic library specifically designed for integration into High-Frequency Trading (HFT) systems. It provides essential security features such as data encryption, key management, and data integrity verification using cryptographic signatures and hashing. The module is lightweight, highly modular, and follows industry-standard cryptographic practices, ensuring both security and performance.

## Key Features

- **AES-256 Encryption**: Secure, high-performance symmetric encryption for sensitive data.
- **RSA-2048 Signatures**: Asymmetric cryptography for data integrity and authenticity.
- **SHA-256 & SHA-512 Hashing**: Cryptographic hash functions for fast and secure data verification.
- **Key Management**: Secure generation, storage, and rotation of cryptographic keys.
- **Modular Design**: Easily integrable into existing systems with a well-structured API.

---

## Prerequisites

To build and use the `security_module`, ensure the following dependencies are installed:

- **CMake**: Version 3.10 or higher
- **GCC or Clang**: Compiler with C11 and C++11 support
- **OpenSSL**: Version 1.1 or higher for cryptographic functions

Install the necessary tools on a Debian-based system:
```bash
sudo apt update
sudo apt install cmake gcc libssl-dev
```

---

## Building the Project

### Step 1: Clone the Repository
Clone the project repository to your local machine:
```bash
git clone https://github.com/your-organization/security_module.git
cd security_module
```

### Step 2: Build the Project
Use CMake to generate the build files and compile the project:

```bash
mkdir build
cd build
cmake ..
make
```

This will compile the security module and create the necessary libraries and executables in the `build/` directory.

### Step 3: Install the Library
To install the `security_module` and its headers into your system, run:
```bash
sudo make install
```

The default installation path is `/usr/local`, but you can customize it by setting the `CMAKE_INSTALL_PREFIX` variable during the CMake configuration.

---

## Usage

The `security_module` provides functions for encryption, decryption, key management, and hashing. Below is an example of how to use the module for encrypting data with AES-256:

### Example: AES-256 Encryption
```cpp
#include <iostream>
#include "security_module/security.h"

int main() {
    const char *plaintext = "Sensitive Data";
    uint8_t aes_key[32] = { /* 256-bit AES key */ };

    // Encrypt the plaintext
    encryption_result_t encrypted_result;
    int ret = aes_encrypt((const uint8_t *)plaintext, strlen(plaintext), aes_key, sizeof(aes_key), &encrypted_result);
    if (ret == 0) {
        std::cout << "Data encrypted successfully!" << std::endl;
    } else {
        std::cerr << "Encryption failed with error code: " << ret << std::endl;
    }

    // Remember to free the result after use
    encryption_result_free(&encrypted_result);
    return 0;
}
```

### Example: Key Generation and Management
The module also provides utilities for secure key management, including key generation and rotation.

- **Generate a new AES key**:
    ```bash
    openssl rand -hex 32 > /path/to/keyfile
    ```

- **Automated key rotation**: The key rotation process can be automated using the provided script:
    ```bash
    sudo ./scripts/key_rotation.sh
    ```

---

## Running Tests

The `security_module` includes a comprehensive suite of unit tests to validate its functionality. The tests cover encryption, decryption, key management, and hashing.

### Running All Tests
To run the tests, first ensure that the project is built, and then execute the following command in the `build/` directory:

```bash
ctest
```

Alternatively, individual test executables can be run directly:

```bash
./bin/test_security
./bin/test_key_manager
./bin/test_hash_utils
```

Each test suite will validate the correctness and integrity of the respective module components.

---

## Project Structure

The `security_module` is organized into the following directories:

```bash
/security_module
|--- CMakeLists.txt         # Project configuration file
|--- include/               # Public header files
|    |--- security_module/
|         |--- security.h
|         |--- key_manager.h
|         |--- hash_utils.h
|--- src/                   # Implementation files
|    |--- security.cpp
|    |--- key_manager.cpp
|    |--- hash_utils.cpp
|--- tests/                 # Unit test source files
|    |--- test_security.cpp
|    |--- test_key_manager.cpp
|    |--- test_hash_utils.cpp
|--- scripts/               # Utility scripts for key management
|    |--- key_rotation.sh
|--- doc/                   # Documentation files
|    |--- README.md
|    |--- SECURITY_ARCHITECTURE.md
```

---

## Error Handling and Debugging

All functions within the `security_module` return standardized error codes:

- `0` – Success
- `-EINVAL` – Invalid arguments
- `-ENOMEM` – Memory allocation failure
- `-EIO` – Input/output error (typically related to cryptographic operations)

### Debugging OpenSSL Errors

In case of OpenSSL-related errors, make sure to use `ERR_print_errors_fp(stderr)` to output detailed error information.

Example:
```cpp
if (ret != 1) {
    ERR_print_errors_fp(stderr);  // Print detailed OpenSSL error messages
}
```

---

## Contributing

We welcome contributions to improve the `security_module`. If you'd like to contribute, please follow these steps:

1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Write clear, concise commit messages.
4. Ensure that all tests pass before submitting a pull request.
5. Submit your pull request for review.

---

## Contact

For any questions or inquiries, please contact the maintainers at `support@dkp_dig.com`.
