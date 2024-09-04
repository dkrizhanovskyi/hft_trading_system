#include <gtest/gtest.h>
#include "order_executor.h"

// Test to ensure that orders can be sent without throwing exceptions
TEST(OrderExecutorTests, CanSendOrder) {
    // Initialize the OrderExecutor with a fake exchange URL
    OrderExecutor executor("http://fake.exchange");

    // Test that the sendOrder method does not throw an exception
    EXPECT_NO_THROW(executor.sendOrder("Buy 100 shares"));
}

// Test to ensure that order status can be checked and returns a valid result
TEST(OrderExecutorTests, CanCheckOrderStatus) {
    // Initialize the OrderExecutor with a fake exchange URL
    OrderExecutor executor("http://fake.exchange");

    // Test that checking the status of an order works (assuming orderId = 1 is valid)
    int orderId = 1;
    EXPECT_TRUE(executor.checkOrderStatus(orderId));
}
