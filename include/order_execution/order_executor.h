#ifndef ORDER_EXECUTOR_H
#define ORDER_EXECUTOR_H

#include <string>
#include "exchange_connector.h"

// The OrderExecutor class is responsible for managing the process of sending orders to the exchange
// and checking their status. It uses the ExchangeConnector class to interact with the exchange API.
class OrderExecutor {
public:
    // Constructor that initializes the exchange connector with a given exchange URL.
    // The connection to the exchange is established upon construction.
    OrderExecutor(const std::string& exchangeUrl);

    // Method to send an order to the exchange.
    // It takes the order details as a string and sends the order if the connection to the exchange is active.
    void sendOrder(const std::string& orderDetails);

    // Method to check the status of an order.
    // Takes an order ID and returns true if the order is complete.
    bool checkOrderStatus(int orderId) const;

private:
    // The exchange connector responsible for communicating with the exchange.
    ExchangeConnector exchangeConnector_;

    // Helper method to generate a unique order ID for each order.
    int generateOrderId() const;
};

#endif // ORDER_EXECUTOR_H
