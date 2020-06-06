#include <string>
#include "./clientCommandProcessor.h"
client::CommandProcessor::~CommandProcessor() {}
client::NumberCommandProcessor::NumberCommandProcessor() {}
client::HelpCommandProcessor::HelpCommandProcessor() {}
client::InvalidCommandProcessor::InvalidCommandProcessor() {}
client::SurrenderCommandProcessor::SurrenderCommandProcessor() {}
client::NumberCommandProcessor::~NumberCommandProcessor() {}
client::HelpCommandProcessor::~HelpCommandProcessor() {}
client::InvalidCommandProcessor::~InvalidCommandProcessor() {}
client::SurrenderCommandProcessor::~SurrenderCommandProcessor() {}

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

std::string client::HelpCommandProcessor::operator()(
    std::string const command,
    client::Client& client) {
    if (command != "AYUDA") return "";
    return client.help();
}

std::string client::SurrenderCommandProcessor::operator()(
    std::string const command,
    client::Client& client) {
    if (command != "RENDIRSE") return "";
    return client.surrender();
}

std::string client::InvalidCommandProcessor::operator()(
    std::string const command,
    client::Client& client) {
    return client.invalid();    
}
