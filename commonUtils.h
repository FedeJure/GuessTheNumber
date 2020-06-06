#ifndef UTILS_H_
#define UTILS_H_
#include <vector>
#include <string>
namespace common
{
    uint32_t getNumberFromBigEndian(std::vector<unsigned char> buffer);
    uint16_t getNumberFromBigEndianShort(std::vector<unsigned char> number);
    std::vector<unsigned char> getBigEndianBuffer(uint16_t num);
    std::vector<unsigned char> getBigEndianBuffer(uint32_t num);
} // namespace common


#endif
