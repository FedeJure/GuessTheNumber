#include <string>
#include "server.h"
#include "./commonDebug.h"

server::Server::Server(std::string& numbersFileName,std::string& service)
    : running(true),
      fileReader(numbersFileName),
      localSocket(service, MAX_CONNECTIONS) {
    thread = std::thread(&server::Server::start, this);
    std::cout<<"Init server with fd: "<< localSocket.Fd()<< std::endl;
}

void server::Server::start() {
    while (running) {
        common::Socket peer = localSocket.acceptConnection();
        std::string numberToGuess = fileReader.getNext();
        ClientConnection* connection =
            new ClientConnection(peer, numberToGuess);
        connections.push_back(std::move(connection));
        for (size_t i = 0; i < connections.size(); i++) {
            ClientConnection* con = connections[i];
            if (!con->isRunning()) {
                std::cout<<"Connection removed from clients"<< std::endl;
                con->stop();
                connections.erase(connections.begin()+i);
                delete con;
            }
        }
    }
}

server::Server::~Server() {}
