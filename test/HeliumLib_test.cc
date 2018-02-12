#include "gtest/gtest.h"
#include "HeliumLib/packet.hpp"

#include <vector>

TEST(PacketTest, VectorChecksum) {
    std::vector<uint8_t> test;
    test.push_back(static_cast<uint8_t>(0xff));
    test.push_back(static_cast<uint8_t>(0x42));

    EXPECT_EQ(0x4140, get_checksum(test));
}
