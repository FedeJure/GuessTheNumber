#include <string>
#include <exception>
#include "./clientArgumentHandler.h"

client::ArgumentHandler::ArgumentHandler(int argc, char* argv[]) {
    if (argc != 3) throw std::exception();
    host = std::string(argv[1]);
    service = std::string(argv[2]);
}

std::string& client::ArgumentHandler::getHost() {
    return host;
}

std::string& client::ArgumentHandler::getService() {
    return service;
}
