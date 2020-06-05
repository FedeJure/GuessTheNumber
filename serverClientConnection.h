#ifndef CLIENT_CONNECTION_H_
#define CLIENT_CONNECTION_H_
#include <thread>
#include <atomic>
#include <string>
#include <vector>
#include "./serverCommandProcessor.h"
#include "./commonSocket.h"
namespace server
{
    class CommandProcessor;
    class ClientConnection {
        std::thread thread;
        std::atomic<bool> keepTalking;
        std::atomic<bool> running;
        common::Socket socket;
        std::string number;
        std::vector<CommandProcessor*>* processors;

        public:
        explicit ClientConnection(common::Socket providedSocket,
            std::string numberToGuess,
            std::vector<CommandProcessor*>& processors);
        void stop();
        bool isRunning();
        std::string receiveNumber();
        ~ClientConnection();

        private:
        void start();
    };
} // namespace server


#endif
