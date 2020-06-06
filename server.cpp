#include <string>
#include <utility>
#include "server.h"

server::Server::Server(std::string& numbersFileName,std::string& service)
    : running(true),
      fileReader(numbersFileName),
      localSocket(service, MAX_CONNECTIONS) {
    thread = std::thread(&server::Server::start, this);
    processors.push_back(std::move(new HelpCommandProcessor()));
    processors.push_back(std::move(new SurrenderCommandProcessor()));
    processors.push_back(std::move(new NumberCommandProcessor()));
}

void server::Server::start() {
    while (running) {
        try {
            common::Socket peer = localSocket.acceptConnection();
            std::string numberToGuess = fileReader.getNext();
            
            ClientConnection* connection =
                new ClientConnection(peer, numberToGuess, processors);
            connections.push_back(std::move(connection));
            if (running )cleanDeadConnections();
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
    cleanAllConnections();
    for (CommandProcessor* processor : processors) {
        delete processor;
    }
    
    thread.join();
    printStadistics();
}

void server::Server::cleanDeadConnections() {
    std::unique_lock<std::mutex> lock(m);
    size_t size = connections.size();
    int eliminatedCount = 0;
    for (size_t i = 0; i < size; i++) {
        ClientConnection* con = connections[i];
        if (!con->isRunning()) {
            con->isWinner() ? winnersCount++ : losersCount++;
            connections.erase(connections.begin()+i-eliminatedCount);
            eliminatedCount++;
            delete con;
        }
    }
}

void server::Server::cleanAllConnections() {
    std::unique_lock<std::mutex> lock(m);
    size_t size = connections.size();
    for (size_t i = 0; i < size; i++) {
        ClientConnection* con = connections.back();
        con->isWinner() ? winnersCount++ : losersCount++;
        delete con;
    }
}

void server::Server::printStadistics() {
    std::cout<<"Estadísticas:​\n";
    std::cout<<"\tGanadores:​  "+std::to_string(winnersCount);
    std::cout<<"\n\tPerdedores:​ "+std::to_string(losersCount)<<"\n";
}
