#ifndef SERVER_H_
#define SERVER_H_
#include <string>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
#include "./serverClientConnection.h"
#include "./serverFileReader.h"
#include "./commonSocket.h"
#include "./serverCommandProcessor.h"
#define MAX_CONNECTIONS 20


namespace server
{
    class Server {
        std::mutex m;
        std::condition_variable notifier;
        std::vector<ClientConnection*> connections;
        std::vector<CommandProcessor*> processors;
        bool running;
        server::FileReader fileReader;
        common::SocketServer localSocket;
        std::thread thread;
        int winnersCount = 0;
        int losersCount = 0;
        void start();
        void cleanDeadConnections();
        void printStadistics();
        void cleanAllConnections();

        public:
        Server(std::string& numbersFileName,
                std::string& service);
        ~Server();
    };
} // namespace server


#endif
