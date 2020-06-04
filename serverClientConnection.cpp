#include <thread>
#include <iostream>
#include <vector>
#include "./commonSocket.h"
#include "./serverClientConnection.h"

server::ClientConnection::ClientConnection(common::Socket providedSocket)
    : keepTalking(true), running(true), socket(providedSocket) {
    thread = std::thread(&server::ClientConnection::start, this);
}

server::ClientConnection::~ClientConnection() {
    stop();
}

void server::ClientConnection::start() {
    try {
        std::vector<char> buffer(10);
        socket.receiveBuffer(buffer);
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
