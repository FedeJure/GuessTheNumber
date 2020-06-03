#ifndef SOCKET_H_
#define SOCKET_H_
#include <string>
#include <vector>
#include <netinet/in.h>

namespace common
{
    class Socket {
        protected:
        int fd;
        std::string service;
        sockaddr_in ip4addr;
        void acquireFd();
        void setOptions();

        public:
        explicit Socket(std::string& service);
        virtual size_t sendBuffer(char* buffer, size_t length);
        virtual size_t receiveBuffer(char* buffer, size_t length);
        virtual ~Socket();
    };

    class SocketServer : Socket {
        int maxConnections;
        std::vector<int> connected_clients;

        public:
        SocketServer(std::string& service, int maxConnection);
        int acceptConnection();
        ~SocketServer();

        private:
        void bindSocket();
        void startListen();
    };

    class SocketClient : Socket {
        std::string host;

        public:
        SocketClient(std::string& providedHost, std::string& service);
        ~SocketClient();

        private:
        void connectSocket();        
    };
} // namespace common


#endif
