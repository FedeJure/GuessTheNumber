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
    class ValidationDto {
        public:
        bool valid;
        int goodCount;
        int regularCount;
        int wrongCount;

        ValidationDto(int pgood, int pregular, int pwrong, bool pvalid)
            :valid(pvalid),
            goodCount(pgood),
            regularCount(pregular),
            wrongCount(pwrong){}
        std::string toString();
    };
    class CommandProcessor;
    class ClientConnection {
        std::thread thread;
        std::atomic<bool> keepTalking;
        std::atomic<bool> running;
        common::Socket socket;
        std::string numberToGuess;
        std::vector<CommandProcessor*>* processors;
        int attempts = 10;

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
        server::ValidationDto validate(uint32_t num);
    };
} // namespace server


#endif
