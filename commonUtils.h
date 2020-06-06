#ifndef UTILS_H_
#define UTILS_H_
#include <vector>
#include <string>
namespace common
{
    uint32_t getNumberFromBigEndiann(std::vector<unsigned char> buffer);
    std::vector<unsigned char> getBigEndianBuffer(uint16_t num);
    std::vector<unsigned char> getBigEndianBuffer(uint32_t num);
    bool isLocalBigEndian();
} // namespace common


#endif
