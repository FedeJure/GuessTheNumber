#ifndef COMMAND_PROCESSOR_H_
#define COMMAND_PROCESSOR_H_
#include <string>
#include <mutex>
#include "./serverClientConnection.h"


namespace server {
    class ClientConnection;

    class CommandProcessor {
        protected:
        std::mutex m;

        public:
        virtual std::string operator()(char command,
            server::ClientConnection& client) = 0;
        virtual ~CommandProcessor();
    };

    class NumberCommandProcessor : public CommandProcessor {
        public:
        NumberCommandProcessor();
        ~NumberCommandProcessor();
        virtual std::string operator()(char command,
            server::ClientConnection& client);
    };

    class HelpCommandProcessor : public CommandProcessor {
        public:
        HelpCommandProcessor();
        ~HelpCommandProcessor();
        virtual std::string operator()(char command,
            server::ClientConnection& client);
    };

    class SurrenderCommandProcessor : public CommandProcessor {
        public:
        SurrenderCommandProcessor();
        ~SurrenderCommandProcessor();
        virtual std::string operator()(char command,
            server::ClientConnection& client);
    };
} // namespace server

#endif
