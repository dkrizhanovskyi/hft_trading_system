# HFT Trading System

## Project Overview
This is a High-Frequency Trading (HFT) system designed to test various trading strategies through backtesting, as well as to manage risk with a set of defined risk strategies. The system includes a modular design for strategies, risk management, logging, and monitoring, allowing for easy expansion and customization.

## Features
- **Backtesting**: Simulates trades on historical data to assess strategy performance.
- **Trading Strategies**:
  - Scalping
  - Mean Reversion
  - Custom strategies can be easily added.
- **Risk Management**:
  - Max Drawdown Strategy
  - Exposure Limit Strategy
  - Support for additional risk strategies.
- **Logging and Monitoring**: Captures key metrics and logs during system execution.
- **Docker and Kubernetes Support**: The system can be containerized using Docker and orchestrated with Kubernetes.

## Installation

### Prerequisites
- **CMake**: Make sure CMake is installed.
- **GCC**: C++ compiler for building the project.
- **Google Test**: For running the unit tests.
- **Docker** (optional): To run the system in a containerized environment.

### Building the Project

1. Clone the repository:
   ```bash
   git clone https://github.com/dkrizhanovskyi/hft_trading_system.git
   cd hft_trading_system
   ```

2. Build the project:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

### Running the Application

Once the project is built, you can run the system using the following command:

```bash
./HFTTradingSystem
```

### Running with Docker

1. Build the Docker image:
   ```bash
   docker build -t hft_trading_system .
   ```

2. Run the container:
   ```bash
   docker run -p 8080:8080 hft_trading_system
   ```

### Running the Tests

Unit tests are located in the `tests/` directory. To run the tests, use the provided script or run them manually:

```bash
./scripts/run_tests.sh
```

Alternatively, if you are using CMake:
```bash
cd build
ctest --output-on-failure
```

## Usage

- **Backtesting**: The system allows you to run backtests using historical data. Strategies are configurable through the `strategy_manager` module.
- **Risk Management**: Implement risk strategies to avoid significant losses during trading. Custom risk strategies can be added.
- **Logging**: All trades and system metrics are logged, making it easier to track system performance.

## Configuration

Configurations are stored in `include/config/settings.h`. Key parameters such as file paths for historical data, strategy thresholds, and risk limits can be adjusted here.

Example:
```cpp
// include/config/settings.h
const std::string HISTORICAL_DATA_FILE = "data/historical_data.csv";
const double MAX_DRAWDOWN_LIMIT = 0.2;
const int SCALPING_STRATEGY_THRESHOLD = 5;
```

## Deployment

### Using Kubernetes

1. Deploy the application using Kubernetes:
   ```bash
   kubectl apply -f kubernetes/deployment.yaml
   kubectl apply -f kubernetes/service.yaml
   ```

2. Check the status of pods and services:
   ```bash
   kubectl get pods
   kubectl get services
   ```

### Using Terraform

1. Initialize Terraform:
   ```bash
   cd terraform
   terraform init
   ```

2. Apply the Terraform configuration:
   ```bash
   terraform apply
   ```

## Contributing

Feel free to fork this repository and contribute by submitting pull requests. Please ensure that your changes are well tested and documented.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
