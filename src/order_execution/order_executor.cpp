// src/order_execution/order_executor.cpp

#include "order_executor.h"
#include <iostream>

OrderExecutor::OrderExecutor(const std::string& exchangeUrl)
    : exchangeConnector_(exchangeUrl) {
    exchangeConnector_.connect();  // Connect to the exchange during initialization
}

void OrderExecutor::sendOrder(const std::string& orderDetails) {
    if (exchangeConnector_.isConnected()) {
        int orderId = generateOrderId();
        std::cout << "Order sent to exchange. Order ID: " << orderId 
                  << ", Details: " << orderDetails << std::endl;
    } else {
        std::cout << "Failed to send order. Not connected to the exchange." << std::endl;
    }
}

bool OrderExecutor::checkOrderStatus(int orderId) const {
    // Simulate checking order status (replace with actual exchange API interaction)
    std::cout << "Order " << orderId << " is complete." << std::endl;
    return true;
}

int OrderExecutor::generateOrderId() const {
    static int currentId = 0;
    return ++currentId;  // Increment the order ID for each new order
}
