#include <gtest/gtest.h>
#include "order_executor.h"

TEST(OrderExecutorTests, CanSendOrder) {
    OrderExecutor executor("http://fake.exchange");
    EXPECT_NO_THROW(executor.sendOrder("Buy 100 shares"));
}

TEST(OrderExecutorTests, CanCheckOrderStatus) {
    OrderExecutor executor("http://fake.exchange");
    int orderId = 1;
    EXPECT_TRUE(executor.checkOrderStatus(orderId));
}
