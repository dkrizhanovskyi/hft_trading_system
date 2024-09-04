// src/order_execution/exchange_connector.cpp

#include "exchange_connector.h"
#include <iostream>  // For output (e.g., connection status)

ExchangeConnector::ExchangeConnector(const std::string& exchangeUrl)
    : exchangeUrl_(exchangeUrl), connected_(false) {}

bool ExchangeConnector::connect() {
    // Simulate connection logic (replace with actual connection code)
    connected_ = true;
    std::cout << "Connected to exchange at: " << exchangeUrl_ << std::endl;
    return connected_;
}

void ExchangeConnector::disconnect() {
    // Simulate disconnection logic
    connected_ = false;
    std::cout << "Disconnected from exchange." << std::endl;
}

bool ExchangeConnector::isConnected() const {
    return connected_;
}
