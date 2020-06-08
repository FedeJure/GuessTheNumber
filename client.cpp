#include <string>
#include <iostream>
#include <cstring>
#include <cstdint>
#include <vector>
#include "./client.h"
#include "./clientCommandProcessor.h"
#include "./clientHelpCommandProcessor.h"
#include "./clientSurrenderCommandProcessor.h"
#include "./clientNumberCommandProcessor.h"
#include "./clientInvalidCommandProcessor.h"
#include "./commonUtils.h"

client::Client::Client(std::string& providedHost, std::string& providedService)
    : localSocket(providedHost, providedService) {
    NumberCommandProcessor* numberP = new NumberCommandProcessor();
    HelpCommandProcessor* helpP = new HelpCommandProcessor();
    SurrenderCommandProcessor* surrenderP = new SurrenderCommandProcessor();
    InvalidCommandProcessor* invalidP = new InvalidCommandProcessor();
    processors.push_back(numberP);
    processors.push_back(helpP);
    processors.push_back(surrenderP);
    processors.push_back(invalidP);
    start();
}

client::Client::~Client() {
    localSocket.shutdownSocket();
    localSocket.closeSocket();
    for (CommandProcessor* processor : processors) {
        delete processor;
    }
}

void client::Client::start() {
    std::string input;
    while (running) {
        std::cin >> input;
        std::string response;
        for (client::CommandProcessor* processor : processors) {
            response = (*processor)(input, *this);
            if (response != "") break;
        }
        std::cout<<response<<std::endl;
    }
}

std::string client::Client::help() {
    std::vector<unsigned char> toSend = {'h'};
    localSocket.sendBuffer(toSend);
    return getResponse();
}
std::string client::Client::invalid() {
    return "Error: comando inválido. Escriba AYUDA para obtener ayuda";
}
std::string client::Client::number(uint32_t input) {
    std::vector<unsigned char> toSend = {'n'};
    localSocket.sendBuffer(toSend);
    uint16_t number = input;
    std::vector<unsigned char> buffer = common::getBigEndianBuffer(number);
    localSocket.sendBuffer(buffer);
    std::string response = getResponse();
    if (response == "Ganaste" || response == "Perdiste") running = false;
    return response;
}
std::string client::Client::surrender() {
    running = false;
    std::vector<unsigned char> toSend = {'s'};
    localSocket.sendBuffer(toSend);
    return getResponse();
}

std::string client::Client::getResponse() {
    std::vector<unsigned char> length(4);
    localSocket.receiveBuffer(length);
    uint32_t num = common::getNumberFromBigEndian(length);
    std::vector<unsigned char> string(num);
    localSocket.receiveBuffer(string);
    std::string response(string.begin(), string.end());
    return response;
}

