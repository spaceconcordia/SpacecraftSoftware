#ifndef HELIUM_PACKET_H_
#define HELIUM_PACKET_H_

#include <vector>
#include <tuple>

const uint16_t SYNC = 0x4865;

void push_bytes(std::vector<uint8_t> &body, uint16_t pair);
uint16_t get_checksum(std::vector<uint8_t> &body);
std::vector<uint8_t> get_packet(uint16_t command, uint16_t payload_size,
        std::vector<uint8_t> &payload);

#endif
