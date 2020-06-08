#include <string>
#include "./serverHelpCommandProcessor.h"

server::HelpCommandProcessor::HelpCommandProcessor() {}
server::HelpCommandProcessor::~HelpCommandProcessor() {}

std::string server::HelpCommandProcessor::operator()(char command,
            server::ClientConnection& client) {
    if (command != 'h') return "";
    return client.help();
}
