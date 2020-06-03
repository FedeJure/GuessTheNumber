#include <string>
#include "./serverArgumentHandler.h"

std::string& server::ArgumentHandler::getService() {
    return this->service;
}

std::string& server::ArgumentHandler::getNumbersFileName() {
    return this->numbersFileName;
}
