#include <thread>
#include <iostream>
#include "./commonSocket.h"
#include "./serverClientConnection.h"

server::ClientConnection::ClientConnection(int providedFd)
    : fd(providedFd) {
    thread = std::thread(&server::ClientConnection::start, this);
}

server::ClientConnection::~ClientConnection() {
    stop();
}

void server::ClientConnection::start() {
    std::cout << "Client connection start working" << std::endl;
}

void server::ClientConnection::stop() {
    common::closeConnection(fd);
}

bool server::ClientConnection::isRunning() {
    return running;
}
