#ifndef EXCHANGE_CONNECTOR_H
#define EXCHANGE_CONNECTOR_H

#include <string>

// The ExchangeConnector class manages the connection to a trading exchange.
// It provides methods to connect, disconnect, and check the connection status.
class ExchangeConnector {
public:
    // Constructor that takes the URL of the exchange as a parameter.
    ExchangeConnector(const std::string& exchangeUrl);

    // Connect to the exchange.
    // This simulates the connection process and returns true if successful.
    bool connect();

    // Disconnect from the exchange.
    // This simulates the disconnection process.
    void disconnect();

    // Check if the connector is currently connected to the exchange.
    // Returns true if connected, false otherwise.
    bool isConnected() const;

private:
    std::string exchangeUrl_;  // The URL of the exchange to connect to.
    bool connected_;  // Boolean flag indicating the connection status.
};

#endif // EXCHANGE_CONNECTOR_H
