#include <string>
#include "server.h"

server::Server::Server(std::string& numbersFileName,std::string& service)
    : running(true),
      fileReader(numbersFileName),
      localSocket(service, MAX_CONNECTIONS) {
    thread = std::thread(&server::Server::start, this);
}

void server::Server::start() {
    while (running) {
        int clientFd = localSocket.acceptConnection();
        ClientConnection* connection = new ClientConnection(clientFd);
        connections.push_back(connection);
        for (size_t i = 0; i < connections.size(); i++) {
            ClientConnection* con = connections[i];
            if (!con->isRunning()) con->stop();
            connections.erase(connections.begin()+i);
        }
    }
}

server::Server::~Server() {}
