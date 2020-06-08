#include <string>
#include "./clientNumberCommandProcessor.h"
client::NumberCommandProcessor::NumberCommandProcessor() {}
client::NumberCommandProcessor::~NumberCommandProcessor() {}

std::string client::NumberCommandProcessor::operator()(
    std::string const command,
    client::Client& client) {
    uint32_t num;
    try {
        num = std::stoi(command);
    }
    catch(const std::exception& e) {
        return "";
    }
    
    if (num > UINT16_MAX || num < 0)
        return "";
    return client.number(num);
}
