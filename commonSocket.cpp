#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h>
#include <exception>
#include <unistd.h>
#include <string>
#include "./commonSocket.h"

common::Socket::Socket(std::string& providedService)
    : service(providedService){}

common::Socket::~Socket() {
    shutdown(fd, SHUT_RDWR);
    close(fd);
}

size_t common::Socket::sendBuffer(char* buffer, size_t length) {
    size_t sent = 0;
    while (sent < length) {
        size_t sended = send(fd, &buffer[sent], (size_t)length-sent,
            MSG_NOSIGNAL);
        if (sended < 0) throw std::exception();
        sent += sended;
    }
    return sent;
}

size_t common::Socket::receiveBuffer(char* buffer, size_t length) {
    size_t readed_size = 0;
    while (readed_size < length) {
        size_t res = recv(fd, (void*)&buffer[readed_size],
            length-readed_size, 0);
        if (res <= 0) throw std::exception();
        readed_size+=res;
    }
    return readed_size;
}

void common::Socket::acquireFd() {
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        throw std::exception();
}

common::SocketServer::SocketServer(std::string& service, int maxConnections) 
    : common::Socket(service), maxConnections(maxConnections) {
    acquireFd();
    setOptions();
    bindSocket();
    startListen();
}

int common::SocketServer::acceptConnection() {
    size_t socket_size = sizeof(ip4addr);
    int accepted = accept(fd, (struct sockaddr*) &ip4addr,
        (socklen_t*)&socket_size);
    if (accepted < -1) throw std::exception();
    connected_clients.push_back(accepted);
    return accepted;
}


void common::SocketServer::setOptions() {
    ip4addr.sin_family = AF_INET;
    ip4addr.sin_addr.s_addr = INADDR_ANY;
    ip4addr.sin_port = htons(std::stoi(service));
}

void common::SocketServer::bindSocket() {
    int binded = bind(fd, (const struct sockaddr*)&ip4addr,
        sizeof(ip4addr));
    if (binded == -1) {
        throw std::exception();
    }
}

void common::SocketServer::startListen() {
    if (listen(fd, maxConnections) < 0) {
        throw std::exception();
    }
}

common::SocketServer::~SocketServer() {
    for (int clients : connected_clients) {
        close(clients);
    }
}
