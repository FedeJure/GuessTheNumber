#ifndef HELP_COMMAND_PROCESSOR_H_
#define HELP_COMMAND_PROCESSOR_H_
#include <string>
#include <mutex>
#include "./serverCommandProcessor.h"
#include "./serverClientConnection.h"


namespace server {
    class HelpCommandProcessor : public CommandProcessor {
        public:
        HelpCommandProcessor();
        ~HelpCommandProcessor();
        virtual std::string operator()(char command,
            server::ClientConnection& client);
    };
} // namespace server

#endif
