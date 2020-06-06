#ifndef CLIENT_H_
#define CLIENT_H_
#include <string>
#include <vector>
#include "./commonSocket.h"
#include "./clientCommandProcessor.h"

namespace client
{
    class CommandProcessor;
    class Client {
        common::SocketClient localSocket;
        std::vector<client::CommandProcessor*> processors;
        bool running = true;
        void start();
        std::string getResponse();

        public:
        Client(std::string& host, std::string& service);
        std::string help();
        std::string invalid();
        std::string number(uint32_t input);
        std::string surrender();
        ~Client();
    };
} // namespace client


#endif
