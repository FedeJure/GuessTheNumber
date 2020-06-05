#include <thread>
#include <iostream>
#include <vector>
#include <string>
#include "./commonSocket.h"
#include "./serverCommandProcessor.h"
#include "./serverClientConnection.h"

server::ClientConnection::ClientConnection(common::Socket providedSocket,
        std::string numberToGuess,
        std::vector<server::CommandProcessor*>& processors)
    : keepTalking(true), running(true), socket(providedSocket),
        number(numberToGuess) {
    std::cout<<"Init client connection with number: "<<number<<std::endl;
    thread = std::thread(&server::ClientConnection::start, this);
    this->processors = &processors;
}

server::ClientConnection::~ClientConnection() {
    stop();
}

void server::ClientConnection::start() {
    try {
        std::vector<char> command(1);
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

std::string server::ClientConnection::receiveNumber() {
    std::vector<char> number(3);
    socket.receiveBuffer(number);
    return std::string(number.begin(), number.end());
}
