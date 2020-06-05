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
        Socket(int id, sockaddr_in ip4addr);
        int Fd();
        void shutdownSocket();
        void closeSocket();
        virtual size_t sendBuffer(std::vector<unsigned char>& buffer);
        virtual size_t receiveBuffer(std::vector<unsigned char>& buffer);
        virtual ~Socket();
    };

    class SocketServer : public Socket {
        int maxConnections;

        public:
        SocketServer(std::string& service, int mConnections);
        common::Socket acceptConnection();
        ~SocketServer();

        private:
        void bindSocket();
        void startListen();
    };

    class SocketClient : public Socket {
        std::string host;

        public:
        SocketClient(std::string& providedHost, std::string& service);
        ~SocketClient();

        private:
        void connectSocket();        
    };

    void closeConnection(int fd);

    class ClosedConnectionError: virtual public std::exception {
        protected:
        std::string error_message;
        
        public:
        explicit ClosedConnectionError(const std::string& msg):
            error_message(msg)
            {}

        virtual ~ClosedConnectionError() throw() {}
        virtual const char* what() const throw() {
            return error_message.c_str();
        }
    };

} // namespace common


#endif
