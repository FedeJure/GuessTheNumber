#include <string>
#include <iostream>
#include <cstring>
#include <cstdint>
#include <vector>
#include "./client.h"
#include "./clientCommandProcessor.h"

client::Client::Client(std::string& providedHost, std::string& providedService)
    : localSocket(providedHost, providedService) {
    std::cout<<"Init client"<<std::endl;
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
    std::cout<<"Destroy client"<<std::endl;
    localSocket.shutdownSocket();
    localSocket.closeSocket();
}

void client::Client::start() {
    std::string input;
    while (running) {
        std::cin >> input;
        for (client::CommandProcessor* processor : processors) {
            std::string response = (*processor)(input, *this);
            std::cout<<"Response: "<<response<<std::endl;
            if (response != "") break;
        }
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
    std::vector<unsigned char> buffer = getBuffer(number);
    localSocket.sendBuffer(buffer);
    return getResponse();
}
std::string client::Client::surrender() {
    std::string response;
    std::vector<unsigned char> toSend = {'s'};
    localSocket.sendBuffer(toSend);
    return response;
}

uint32_t client::Client::getNumber(std::vector<unsigned char> buffer) {
    int32_t response;
    if (isLocalBigEndian()) {
        response = buffer[0] | buffer[1] | buffer[2] | buffer[2];
        return response;
    }
    response = buffer[3] | buffer[2] | buffer[1] | buffer[0];
    return response;
}

std::string client::Client::getResponse() {
    std::vector<unsigned char> length(4);
    localSocket.receiveBuffer(length);
    uint32_t num = getNumber(length);
    std::vector<unsigned char> string(num + 1);
    localSocket.receiveBuffer(string);
    std::string response(string.begin(), string.end());
    return response;
}

std::vector<unsigned char> client::Client::getBuffer(uint16_t num) {
    std::vector<unsigned char> buffer(2);
    uint16_t netNum = htons(num);
    std::memcpy(buffer.data(), &netNum, 2);
    return buffer;
}

bool client::Client::isLocalBigEndian() {
    int aux = 0x1;
    return ((char*)&aux)[0] == 0;   
}
