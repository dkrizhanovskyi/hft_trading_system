#include "exchange_connector.h"
#include "security.h"  // Подключаем модуль безопасности для шифрования и подписи
#include <iostream>  // For printing connection status
#include <openssl/aes.h>  // For AES encryption

// Constructor that initializes the ExchangeConnector with the exchange URL.
// Initially, the connection status is set to false (disconnected).
ExchangeConnector::ExchangeConnector(const std::string& exchangeUrl)
    : exchangeUrl_(exchangeUrl), connected_(false) {}

// Connect to the exchange.
// This simulates the connection process, encrypts the URL, and prints the connection status. Returns true on success.
bool ExchangeConnector::connect() {
    // Шифруем URL перед подключением
    uint8_t key[AES_BLOCK_SIZE] = { /* инициализируйте ваш ключ шифрования */ };
    encryption_result_t encrypted_url;
    
    int ret = aes_encrypt((const uint8_t*)exchangeUrl_.c_str(), exchangeUrl_.size(), key, AES_BLOCK_SIZE, &encrypted_url);
    if (ret == 0) {
        std::cout << "Successfully encrypted exchange URL." << std::endl;
        
        // Симуляция успешного подключения после шифрования
        connected_ = true;
        std::cout << "Connected to exchange with encrypted URL." << std::endl;
        
        // Здесь можно отправить зашифрованный URL или использовать его в дальнейшем
    } else {
        std::cerr << "Encryption failed. Cannot connect to exchange." << std::endl;
        return false;
    }
    
    encryption_result_free(&encrypted_url);  // Очистка памяти после шифрования
    return connected_;
}

// Disconnect from the exchange.
// This simulates the disconnection process and prints the disconnection message.
void ExchangeConnector::disconnect() {
    connected_ = false;
    std::cout << "Disconnected from exchange." << std::endl;
}

// Check if the connector is currently connected to the exchange.
// Returns true if the connection is active.
bool ExchangeConnector::isConnected() const {
    return connected_;
}
