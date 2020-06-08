#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h>
#include <exception>
#include <unistd.h>
#include <string>
#include <netdb.h>
#include <vector>
#include <iostream>
#include "./commonSocket.h"

common::Socket::Socket(std::string& providedService)
    : service(providedService){
    acquireFd();
    setOptions();
}

common::Socket::Socket(int fd, sockaddr_in ip4addr) {
    this->fd = fd;
    this->ip4addr = ip4addr;
    this->service = ip4addr.sin_port;
}

common::Socket::~Socket() {}

void common::Socket::setOptions() {
    ip4addr.sin_family = AF_INET;
    ip4addr.sin_addr.s_addr = INADDR_ANY;
    ip4addr.sin_port = htons(std::stoi(service));
}

size_t common::Socket::sendBuffer(std::vector<unsigned char>& buffer) {
    size_t sent = 0;
    while (sent < buffer.size()) {
        size_t sended = send(fd, &buffer[sent], buffer.size()-sent,
            MSG_NOSIGNAL);
        if (sended < 0) throw common::ClosedConnectionError("Sending buffer");
        sent += sended;
    }
    return sent;
}

size_t common::Socket::receiveBuffer(std::vector<unsigned char>& buffer) {
    size_t readed_size = 0;
    while (readed_size < buffer.size()) {
        size_t res = recv(fd, &buffer[readed_size],
            buffer.size()-readed_size, 0);
        if (res <= 0) throw common::ClosedConnectionError("Receiving buffer");
        readed_size+=res;
    }
    return readed_size;
}

void common::Socket::acquireFd() {
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        throw std::exception();
}

int common::Socket::Fd() {
    return fd;
}

void common::Socket::shutdownSocket() {
    shutdown(fd, SHUT_RDWR);
}

void common::Socket::closeSocket() {
    close(fd);
}

common::SocketServer::SocketServer(std::string& service, int mConnections)
    : common::Socket(service), maxConnections(mConnections) {
    bindSocket();
    startListen();
}

common::SocketServer::~SocketServer() {
}

common::Socket common::SocketServer::acceptConnection() {
    size_t socket_size = sizeof(ip4addr);
    int accepted = accept(fd, (sockaddr*) &ip4addr,
        (socklen_t*)&socket_size);
    if (accepted < 0) throw std::exception();
    return std::move(common::Socket(accepted, ip4addr));
}

void common::SocketServer::bindSocket() {
    int binded = bind(fd, (const sockaddr*)&ip4addr,
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

common::SocketClient::SocketClient(std::string& providedHost,
                                        std::string& service)
    : common::Socket(service), host(providedHost) {
        connectSocket();
}

void common::SocketClient::connectSocket() {
    struct sockaddr_in ip4addr = {0};
    struct addrinfo *ai_list, *ptr = {0};
    struct addrinfo hints = {0};
    int res;
    setOptions();
    try {
        res = getaddrinfo(host.c_str(), service.c_str(), &hints, &ai_list);
        if (res < 0 ) throw std::exception();
        for (ptr = ai_list; (void*)ptr != NULL; ptr = ptr->ai_next) {
            ip4addr.sin_addr.s_addr = *((uint32_t*) &
                (((struct sockaddr_in*)ptr->ai_addr)->sin_addr));
            ip4addr.sin_family = AF_INET;
            ip4addr.sin_port = htons(atoi(service.c_str()));
            res = connect(fd, (struct sockaddr*)&ip4addr, sizeof(ip4addr));
            if (res == -1) continue;
        }
        if (ptr == NULL) {
            freeaddrinfo(ai_list); 
        }
    }
    catch(const std::exception& e) {
        throw std::exception();
    }
}

common::SocketClient::~SocketClient() {}

void common::closeConnection(int fd) {
    close(fd);
}
