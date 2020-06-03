#ifndef ARGUMENT_HANDLER_H_
#define ARGUMENT_HANDLER_H_
#include <string>
#include <exception>

namespace server
{
    class ArgumentHandler {
        std::string service;
        std::string numbersFileName;

        public:
        ArgumentHandler(int argc, char* argv[]) {
            if (argc != 3) throw std::exception();
            service = std::string(argv[1]);
            numbersFileName = std::string(argv[2]);
        }

        std::string& getService();
        std::string& getNumbersFileName();
    };
    
} // server

#endif
