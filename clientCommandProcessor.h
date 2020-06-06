#ifndef COMMAND_PROCESSOR_H_
#define COMMAND_PROCESSOR_H_
#include <string>
#include "./client.h"


namespace client {
    class Client;

    class CommandProcessor {
        public:
        virtual std::string operator()(std::string const command,
            client::Client& client) = 0;
        virtual ~CommandProcessor();
    };
 
    class NumberCommandProcessor : public CommandProcessor {
        public:
        NumberCommandProcessor();
        ~NumberCommandProcessor();
        virtual std::string operator()(std::string const command,
            client::Client& client);
    };

    class HelpCommandProcessor : public CommandProcessor {
        public:
        HelpCommandProcessor();
        ~HelpCommandProcessor();
        virtual std::string operator()(std::string const command,
            client::Client& client);
    };

    class SurrenderCommandProcessor : public CommandProcessor {
        public:
        SurrenderCommandProcessor();
        ~SurrenderCommandProcessor();
        virtual std::string operator()(std::string const command,
            client::Client& client);
    };

    class InvalidCommandProcessor : public CommandProcessor {
        public:
        InvalidCommandProcessor();
        ~InvalidCommandProcessor();
        virtual std::string operator()(std::string const command,
            client::Client& client);
    };
} // namespace client

#endif
