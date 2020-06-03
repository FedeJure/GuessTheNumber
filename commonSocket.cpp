#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h>
#include <exception>
#include <unistd.h>
#include <string>
#include "./commonSocket.h"


common::Socket::Socket(std::string& service) {
    acquireFd();
}

common::Socket::Socket(std::string& host, std::string& service) {
    acquireFd();
}

void common::Socket::acquireFd() {
    if ((this->fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        throw std::exception();
}

common::Socket::~Socket() {
    shutdown(this->fd, SHUT_RDWR);
    close(this->fd);
}
