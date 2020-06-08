#include <string>
#include "./serverSurrenderCommandProcessor.h"

server::SurrenderCommandProcessor::SurrenderCommandProcessor() {}
server::SurrenderCommandProcessor::~SurrenderCommandProcessor() {}

std::string server::SurrenderCommandProcessor::operator()(char command,
            server::ClientConnection& client) {
    if (command != 's') return "";
    return client.surrender();
}
