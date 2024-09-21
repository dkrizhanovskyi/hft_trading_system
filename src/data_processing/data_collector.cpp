#include "data_collector.h"
#include "security.h"  // Подключаем модуль безопасности для шифрования
#include <iostream>
#include <cstring>
#include <openssl/aes.h>

// Constructor to initialize the data source and set the initial collection state to false (inactive).
DataCollector::DataCollector(const std::string& source)
    : source_(source), collecting_(false) {}

// Start the data collection process and indicate that data is now being collected.
void DataCollector::startCollection() {
    collecting_ = true;
    std::cout << "Started collecting data from source: " << source_ << std::endl;

    // Пример: собираем данные (здесь мы используем строку в качестве примера)
    std::string collected_data = "Sensitive data collected from " + source_;

    // Шифрование данных с использованием AES-256
    uint8_t key[AES_BLOCK_SIZE] = { /* инициализируйте ваш ключ */ };
    encryption_result_t encrypted_data;
    int ret = aes_encrypt(reinterpret_cast<const uint8_t*>(collected_data.c_str()), collected_data.size(), key, AES_BLOCK_SIZE, &encrypted_data);
    
    if (ret == 0) {
        std::cout << "Data successfully encrypted." << std::endl;
        // Здесь вы можете использовать зашифрованные данные
    } else {
        std::cerr << "Encryption failed!" << std::endl;
    }

    // Очистка после шифрования
    encryption_result_free(&encrypted_data);
}

// Stop the data collection process and set the collecting flag to false.
void DataCollector::stopCollection() {
    collecting_ = false;
    std::cout << "Stopped collecting data from source: " << source_ << std::endl;
}

// Return the current status of data collection (true if active, false if inactive).
bool DataCollector::isCollecting() const {
    return collecting_;
}
