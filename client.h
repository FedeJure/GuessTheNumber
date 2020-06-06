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
        uint32_t getNumber(std::vector<unsigned char> buffer);
        std::vector<unsigned char> getBuffer(uint16_t num);
        std::string getResponse();
        bool isLocalBigEndian();

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
