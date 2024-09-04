// src/order_execution/exchange_connector.h

#ifndef EXCHANGE_CONNECTOR_H
#define EXCHANGE_CONNECTOR_H

#include <string>

class ExchangeConnector {
public:
    // Constructor with exchange URL
    ExchangeConnector(const std::string& exchangeUrl);

    // Connect to the exchange
    bool connect();

    // Disconnect from the exchange
    void disconnect();

    // Check if connected to the exchange
    bool isConnected() const;

private:
    std::string exchangeUrl_;  // URL of the exchange
    bool connected_;  // Connection status
};

#endif // EXCHANGE_CONNECTOR_H
