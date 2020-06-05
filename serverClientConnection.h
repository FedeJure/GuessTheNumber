#ifndef CLIENT_CONNECTION_H_
#define CLIENT_CONNECTION_H_
#include <thread>
#include <atomic>
#include <string>
#include "./commonSocket.h"
namespace server
{
    class ClientConnection {
        std::thread thread;
        std::atomic<bool> keepTalking;
        std::atomic<bool> running;
        common::Socket socket;
        std::string number;

        public:
        explicit ClientConnection(common::Socket providedSocket,
                                    std::string numberToGuess);
        void stop();
        bool isRunning();
        ~ClientConnection();

        private:
        void start();
    };
} // namespace server


#endif
