#include <iostream>
#include <string>
#include "./serverArgumentHandler.h"
#include "./server.h"
#define SERVER_SUCESS 0
#define SERVER_ERROR 1

int main(int argc, char* argv[]) {
    try {
        server::ArgumentHandler argumentHandler(argc, argv);
        server::Server server(argumentHandler.getNumbersFileName(),
                                argumentHandler.getService());
        std::string input;
        do {
            std::cin >> input;
        } while (input != "q");
    }
    catch(const std::exception& e) {
        return SERVER_ERROR;
    }
    return SERVER_SUCESS;
}
