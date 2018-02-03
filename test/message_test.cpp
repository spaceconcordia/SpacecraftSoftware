#include "gtest/gtest.h"
#include "HelloLib/message.hpp"

TEST(message_test, content)
{
    EXPECT_EQ(get_message(), "Hello world!");
}
