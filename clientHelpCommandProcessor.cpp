#include <string>
#include "./clientHelpCommandProcessor.h"
client::HelpCommandProcessor::HelpCommandProcessor() {}
client::HelpCommandProcessor::~HelpCommandProcessor() {}

std::string client::HelpCommandProcessor::operator()(
    std::string const command,
    client::Client& client) {
    if (command != "AYUDA") return "";
    return client.help();
}
