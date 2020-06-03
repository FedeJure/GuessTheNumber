#ifndef SOCKET_H_
#define SOCKET_H_
#include <string>

namespace common
{
    class Socket {
        int fd;

        public:
        explicit Socket(std::string& service);
        Socket(std::string& host, std::string& service);
        ~Socket();

        private:
        void acquireFd();
    };
} // namespace server


#endif
