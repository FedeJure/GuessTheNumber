#ifndef ARGUMENT_HANDLER_H_
#define ARGUMENT_HANDLER_H_
#include <string>


namespace client
{
    class ArgumentHandler {
        std::string host;
        std::string service;

        public:
        ArgumentHandler(int argc, char* argv[]);
        std::string& getHost();
        std::string& getService();
    };
} // namespace client


#endif
