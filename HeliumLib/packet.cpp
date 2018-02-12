#include "HeliumLib/packet.hpp"

// packet ->
// header (8), payload (0-255), payload checksum A (1), payload checksum b (1)

// header ->
// sync chars (2), command type (2), payload size (2), header checksum A (1), header checksum B (1)

void push_bytes(std::vector<uint8_t> &body, uint16_t pair) {
    body.push_back(static_cast<uint8_t>(pair >> 8));
    body.push_back(static_cast<uint8_t>(pair));
}

uint16_t get_checksum(std::vector<uint8_t> &body) {
    uint8_t ck_a, ck_b;
    ck_a = ck_b = 0;

    for (unsigned int i = 0; i < body.size(); i++) {
        ck_a += body[i];
        ck_b += ck_a;
    }

    uint16_t checksum = (ck_a << 8) | ck_b;
    return checksum;
}

std::vector<uint8_t> get_packet(uint16_t command, uint16_t payload_size,
        std::vector<uint8_t> &payload) {
    std::vector<uint8_t> message;

    // First, we add the header. Add sync chars
    push_bytes(message, SYNC);
    push_bytes(message, command);
    push_bytes(message, payload_size);

    // Get header without the constants for checksum
    std::vector<uint8_t> header = std::vector<uint8_t>(message.begin()+2,
            message.end());
    push_bytes(message, get_checksum(header));

    // Insert main payload
    message.insert(message.end(), payload.begin(), payload.end());

    // Append checksum
    push_bytes(message, get_checksum(payload));

    return message;
}
