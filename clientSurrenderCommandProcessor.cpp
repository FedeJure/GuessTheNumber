#include <string>
#include "./clientSurrenderCommandProcessor.h"
client::SurrenderCommandProcessor::SurrenderCommandProcessor() {}
client::SurrenderCommandProcessor::~SurrenderCommandProcessor() {}

std::string client::SurrenderCommandProcessor::operator()(
    std::string const command,
    client::Client& client) {
    if (command != "RENDIRSE") return "";
    return client.surrender();
}
