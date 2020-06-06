#include <string>
#include "server.h"
#include "./commonDebug.h"

server::Server::Server(std::string& numbersFileName,std::string& service)
    : running(true),
      fileReader(numbersFileName),
      localSocket(service, MAX_CONNECTIONS) {
    thread = std::thread(&server::Server::start, this);
    processors.push_back(new HelpCommandProcessor());
    processors.push_back(new SurrenderCommandProcessor());
    processors.push_back(new NumberCommandProcessor());
}

void server::Server::start() {
    while (running) {
        try {
            common::Socket peer = localSocket.acceptConnection();
            std::string numberToGuess = fileReader.getNext();
            
            ClientConnection* connection =
                new ClientConnection(peer, numberToGuess, processors);
            connections.push_back(std::move(connection));
            cleanDeadConnections();
        }
        catch(const std::exception& e) {
            break;
        }
    }
}

server::Server::~Server() {
    running = false;
    localSocket.shutdownSocket();
    localSocket.closeSocket();
    for (const CommandProcessor* processor : processors) {
        delete processor;
    }
    cleanAllConnections();
    thread.join();
    printStadistics();
}

void server::Server::cleanDeadConnections() {
    std::unique_lock<std::mutex> lock(m);
    for (size_t i = 0; i < connections.size(); i++) {
        ClientConnection* con = connections[i];
        if (!con->isRunning()) {
            con->isWinner() ? winnersCount++ : losersCount++;
            con->stop();
            connections.erase(connections.begin()+i);
            delete con;
        }
    }
}

void server::Server::cleanAllConnections() {
    std::unique_lock<std::mutex> lock(m);
    for (size_t i = 0; i < connections.size(); i++) {
        ClientConnection* con = connections[i];
        con->isWinner() ? winnersCount++ : losersCount++;
        con->stop();
        connections.erase(connections.begin()+i);
        delete con;
    }
}

void server::Server::printStadistics() {
    std::cout<<"Estadísticas:​ "<<std::endl;
    std::cout<<"\tGanadores:​ "+std::to_string(winnersCount)<<std::endl;
    std::cout<<"\tPerdedores:​ "+std::to_string(losersCount)<<std::endl;
}
