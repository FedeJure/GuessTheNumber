#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include <cstdint>
#include <netinet/in.h>
#include "./commonUtils.h"

uint32_t common::getNumberFromBigEndian(std::vector<unsigned char> buffer) {
    uint32_t response;
    std::memcpy(&response, buffer.data(), sizeof(response));
    return ntohl(response);
}

uint16_t common::getNumberFromBigEndianShort(
    std::vector<unsigned char> number) {
    uint16_t response;
    std::memcpy(&response, number.data(), sizeof(response));
    return ntohs(response);
}

std::vector<unsigned char> common::getBigEndianBuffer(uint16_t num) {
    std::vector<unsigned char> buffer(2);
    uint16_t netNum = htons(num);
    std::memcpy(buffer.data(), &netNum, 2);
    return buffer;
}
std::vector<unsigned char> common::getBigEndianBuffer(uint32_t num) {
    std::vector<unsigned char> buffer(4);
    uint32_t netNum = htonl(num);
    std::memcpy(buffer.data(), &netNum, 4);
    return buffer;
}
