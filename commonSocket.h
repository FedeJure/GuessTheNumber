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

        public:
        explicit Socket(std::string& service);
        virtual void send(char* buffer, size_t length);
        virtual void receive(char* buffer, size_t length);
        virtual ~Socket();
    };

    class SocketServer : Socket {
        int maxConnections;
        std::vector<int> connected_clients;

        public:
        SocketServer(std::string& service, int maxConnection);
        SocketServer(std::string& host, std::string& service);
        int acceptConnection();
        ~SocketServer();

        private:
        void setOptions();
        void bindSocket();
        void startListen();
    };
} // namespace server


#endif
