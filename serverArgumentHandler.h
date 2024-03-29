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
        ArgumentHandler(int argc, char* argv[]);
        std::string& getService();
        std::string& getNumbersFileName();
    };
    
} // server

#endif
