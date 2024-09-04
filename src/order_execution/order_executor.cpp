#include "order_executor.h"
#include <iostream>  // For printing order execution information

// Constructor that initializes the exchange connector with the provided exchange URL.
// The constructor attempts to connect to the exchange upon initialization.
OrderExecutor::OrderExecutor(const std::string& exchangeUrl)
    : exchangeConnector_(exchangeUrl) {
    exchangeConnector_.connect();  // Connect to the exchange during initialization
}

// Sends an order to the exchange.
// If the exchange is connected, a unique order ID is generated and the order is sent.
void OrderExecutor::sendOrder(const std::string& orderDetails) {
    if (exchangeConnector_.isConnected()) {
        int orderId = generateOrderId();
        std::cout << "Order sent to exchange. Order ID: " << orderId 
                  << ", Details: " << orderDetails << std::endl;
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

// Generates a unique order ID by incrementing a static counter.
int OrderExecutor::generateOrderId() const {
    static int currentId = 0;
    return ++currentId;
}
