#include <gtest/gtest.h>
extern "C" {
#include "add.h"
}

TEST(ArithmeticTest, Addition) {
	EXPECT_EQ(add(1, 1), 2);
}
