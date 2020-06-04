#ifndef CLIENT_CONNECTION_H_
#define CLIENT_CONNECTION_H_
#include <thread>
namespace server
{
    class ClientConnection {
        std::thread thread;
        bool running;
        int fd;

        public:
        explicit ClientConnection(int providedFd);
        void stop();
        bool isRunning();
        ~ClientConnection();

        private:
        void start();
    };
} // namespace server


#endif
