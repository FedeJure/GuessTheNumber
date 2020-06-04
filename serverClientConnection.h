#ifndef CLIENT_CONNECTION_H_
#define CLIENT_CONNECTION_H_
#include <thread>
#include <atomic>
#include "./commonSocket.h"
namespace server
{
    class ClientConnection {
        std::thread thread;
        std::atomic<bool> keepTalking;
        std::atomic<bool> running;
        common::Socket socket;

        public:
        explicit ClientConnection(common::Socket providedSocket);
        void stop();
        bool isRunning();
        ~ClientConnection();

        private:
        void start();
    };
} // namespace server


#endif
