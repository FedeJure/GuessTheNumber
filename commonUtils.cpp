#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include <cstdint>
#include <netinet/in.h>
#include "./commonUtils.h"

uint32_t common::getNumberFromBigEndiann(std::vector<unsigned char> buffer) {
    int32_t response;
    if (common::isLocalBigEndian()) {
        response = buffer[0] | buffer[1] | buffer[2] | buffer[2];
        return response;
    }
    response = buffer[3] | buffer[2] | buffer[1] | buffer[0];
    return response;
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
bool common::isLocalBigEndian() {
    int aux = 0x1;
    return ((char*)&aux)[0] == 0; 
}
