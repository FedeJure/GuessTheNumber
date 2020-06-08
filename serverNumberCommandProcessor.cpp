#include <string>
#include "./serverNumberCommandProcessor.h"

server::NumberCommandProcessor::NumberCommandProcessor() {}
server::NumberCommandProcessor::~NumberCommandProcessor() {}

std::string server::NumberCommandProcessor::operator()(char command,
            server::ClientConnection& client) {
    if (command != 'n') return "";
    return client.receiveNumber();
}
