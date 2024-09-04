// src/order_execution/order_executor.h

#ifndef ORDER_EXECUTOR_H
#define ORDER_EXECUTOR_H

#include <string>
#include "exchange_connector.h"

class OrderExecutor {
public:
    // Constructor that initializes the exchange connector
    OrderExecutor(const std::string& exchangeUrl);

    // Method to send an order to the exchange
    void sendOrder(const std::string& orderDetails);

    // Method to check the status of an order
    bool checkOrderStatus(int orderId) const;

private:
    ExchangeConnector exchangeConnector_;  // Connector to the exchange
    int generateOrderId() const;  // Helper method to generate a unique order ID
};

#endif // ORDER_EXECUTOR_H
