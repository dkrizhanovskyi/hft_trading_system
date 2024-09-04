#include "exchange_connector.h"
#include <iostream>  // For printing connection status

// Constructor that initializes the ExchangeConnector with the exchange URL.
// Initially, the connection status is set to false (disconnected).
ExchangeConnector::ExchangeConnector(const std::string& exchangeUrl)
    : exchangeUrl_(exchangeUrl), connected_(false) {}

// Connect to the exchange.
// This simulates the connection process and prints the connection status. Returns true on success.
bool ExchangeConnector::connect() {
    connected_ = true;
    std::cout << "Connected to exchange at: " << exchangeUrl_ << std::endl;
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
