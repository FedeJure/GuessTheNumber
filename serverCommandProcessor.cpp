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
    std::string response = client.receiveNumber();
    return response;
}

std::string server::HelpCommandProcessor::operator()(char command,
            server::ClientConnection& client) {
    if (command != 'h') return "";
    std::string response;
    response.append("Comandos válidos:​\n\t​AYUDA: despliega la");
    response.append(" lista de comandos válidos​\n\t​RENDIRSE: pierde");
    response.append(" el juego automáticamente​\n\t​XXX: Número de");
    response.append(" 3 cifras a ser enviado al servidor para ");
    response.append("adivinar el número secreto");
    return response;
}

std::string server::SurrenderCommandProcessor::operator()(char command,
            server::ClientConnection& client) {
    if (command != 's') return "";
    return "Perdiste";
}
