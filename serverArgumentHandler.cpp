#include <string>
#include "./serverArgumentHandler.h"

server::ArgumentHandler::ArgumentHandler(int argc, char* argv[]) {
    if (argc != 3) throw std::exception();
    service = std::string(argv[1]);
    numbersFileName = std::string(argv[2]);
}

std::string& server::ArgumentHandler::getService() {
    return this->service;
}

std::string& server::ArgumentHandler::getNumbersFileName() {
    return this->numbersFileName;
}
