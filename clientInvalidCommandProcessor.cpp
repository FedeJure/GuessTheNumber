#include <string>
#include "./clientInvalidCommandProcessor.h"
client::InvalidCommandProcessor::InvalidCommandProcessor() {}
client::InvalidCommandProcessor::~InvalidCommandProcessor() {}

std::string client::InvalidCommandProcessor::operator()(
    std::string const command,
    client::Client& client) {
    return client.invalid();    
}
