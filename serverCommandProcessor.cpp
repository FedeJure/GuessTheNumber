#include <string>
#include "./serverCommandProcessor.h"

server::CommandProcessor::~CommandProcessor() {}
server::HelpCommandProcessor::HelpCommandProcessor() {}
server::NumberCommandProcessor::NumberCommandProcessor() {}
server::SurrenderCommandProcessor::SurrenderCommandProcessor() {}
server::HelpCommandProcessor::~HelpCommandProcessor() {}
server::NumberCommandProcessor::~NumberCommandProcessor() {}
server::SurrenderCommandProcessor::~SurrenderCommandProcessor() {}

std::string server::NumberCommandProcessor::operator()(char command,
            server::ClientConnection& client) {
    if (command != 'n') return "";
    return client.receiveNumber();
}

std::string server::HelpCommandProcessor::operator()(char command,
            server::ClientConnection& client) {
    if (command != 'h') return "";
    return client.help();
}

std::string server::SurrenderCommandProcessor::operator()(char command,
            server::ClientConnection& client) {
    if (command != 's') return "";
    return client.surrender();
}
