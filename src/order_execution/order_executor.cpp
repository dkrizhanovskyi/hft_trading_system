#include "order_executor.h"
#include "security.h"  // Подключаем модуль безопасности для подписи
#include <iostream>  // For printing order execution information
#include <atomic>    // For atomic operations in multithreaded environments
#include <xmmintrin.h>  // For SIMD prefetching

// Constructor that initializes the exchange connector with the provided exchange URL.
// The constructor attempts to connect to the exchange upon initialization.
OrderExecutor::OrderExecutor(const std::string& exchangeUrl)
    : exchangeConnector_(exchangeUrl) {
    exchangeConnector_.connect();  // Connect to the exchange during initialization
}

// Sends an order to the exchange.
// If the exchange is connected, a unique order ID is generated and the order is signed and sent.
void OrderExecutor::sendOrder(const std::string& orderDetails) {
    if (exchangeConnector_.isConnected()) {
        // Prefetching the order details into the cache to reduce latency
        _mm_prefetch(orderDetails.data(), _MM_HINT_T0);

        // Подпись ордера с использованием закрытого ключа RSA
        uint8_t private_key[256] = { /* Инициализируйте ваш закрытый ключ */ };
        encryption_result_t signature;
        int ret = sign_data((const uint8_t *)orderDetails.c_str(), orderDetails.size(), private_key, 256, &signature);
        
        if (ret == 0) {
            int orderId = generateOrderId();
            std::cout << "Order sent to exchange. Order ID: " << orderId 
                      << ", Details: " << orderDetails << ", Signature: ";

            // Печать подписи в шестнадцатеричном формате
            for (size_t i = 0; i < signature.data_len; ++i) {
                printf("%02x", signature.data[i]);
            }
            std::cout << std::endl;

            // После использования освобождаем память
            encryption_result_free(&signature);
        } else {
            std::cerr << "Failed to sign the order." << std::endl;
        }
    } else {
        std::cout << "Failed to send order. Not connected to the exchange." << std::endl;
    }
}

// Checks the status of an order.
// For demonstration purposes, this function always returns true and prints the status.
bool OrderExecutor::checkOrderStatus(int orderId) const {
    std::cout << "Order " << orderId << " is complete." << std::endl;
    return true;
}

// Generates a unique order ID by incrementing a static atomic counter.
// This ensures thread-safe generation of unique order IDs in a multithreaded environment.
int OrderExecutor::generateOrderId() const {
    static std::atomic<int> currentId{0};
    return ++currentId;  // Atomically increment and return the order ID
}
