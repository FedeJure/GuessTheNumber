#include <thread>
#include <iostream>
#include <vector>
#include <string>
#include "./commonSocket.h"
#include "./serverCommandProcessor.h"
#include "./serverClientConnection.h"

server::ClientConnection::ClientConnection(common::Socket providedSocket,
        std::string number,
        std::vector<server::CommandProcessor*>& processors)
    : keepTalking(true), running(true), socket(providedSocket),
        numberToGuess(number) {
    std::cout<<"Init client connection with number: "<<numberToGuess<<std::endl;
    thread = std::thread(&server::ClientConnection::start, this);
    this->processors = &processors;
}

server::ClientConnection::~ClientConnection() {
    stop();
}

void server::ClientConnection::start() {
    try {
        std::vector<unsigned char> command(1);
        while (socket.receiveBuffer(command) > 0) {
            for (CommandProcessor* processor : *processors) {
                std::string response = (*processor)(command[0], *this);
                std::cout<<response;
                fflush(stdout);
            }
        }
    }
    catch(const std::exception& e) {
        running = false;
    }
    running = false;
}

void server::ClientConnection::stop() {
    if (thread.joinable()) thread.join();
    socket.shutdownSocket();
    socket.closeSocket();
}

bool server::ClientConnection::isRunning() {
    return running;
}

int32_t bigEndtoLocalEnd(std::vector<unsigned char> number) {
    int aux = 0x1;
    int32_t response;
    bool localIsBig = ((char*)&aux)[0] == 0;
    if (localIsBig) {
        response = number[0] | number[1];
        return response;
    }
    response = number[1] | number[0];
    return response;
}

std::string server::ClientConnection::receiveNumber() {
    std::vector<unsigned char> number(2);
    socket.receiveBuffer(number);
    int32_t received = bigEndtoLocalEnd(number);
    server::ValidationDto validation = validate(received);
    std::vector<std::string> validations;
    if (validation.goodCount > 0)
        validations.push_back(std::to_string(validation.goodCount)+" bien");
    if (validation.regularCount > 0)
        validations.push_back(
            std::to_string(validation.regularCount)+" regular");
    if (validation.wrongCount > 0)
        validations.push_back(std::to_string(validation.wrongCount)+" mal");
    std::string response;
    bool addComma = false;
    for (std::string val: validations) {
        response+= addComma ? ", "+val : val;
        addComma = true;
    }
    return response;
}

server::ValidationDto server::ClientConnection::validate(
        uint32_t num) {
    if (num > 999 || num < 100) {
        return server::ValidationDto(0,0,0,false);
    }
    std::cout<<numberToGuess<<std::endl; fflush(stdout);

    std::string toVerify = std::to_string(num);
    int good(0); int wrong(0); int regular(0);
    for (size_t i = 0; i < 3; i++) {
        if (toVerify[i] == numberToGuess[i]) 
            good++;
        else if (numberToGuess.find(toVerify[i]) != std::string::npos)
            regular++;
        else
            wrong++;
    }
    return server::ValidationDto(good,regular,wrong, true);
}
