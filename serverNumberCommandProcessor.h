#ifndef NUMBER_COMMAND_PROCESSOR_H_
#define NUMBER_COMMAND_PROCESSOR_H_
#include <string>
#include <mutex>
#include "./serverCommandProcessor.h"
#include "./serverClientConnection.h"


namespace server {

    class NumberCommandProcessor : public CommandProcessor {
        public:
        NumberCommandProcessor();
        ~NumberCommandProcessor();
        virtual std::string operator()(char command,
            server::ClientConnection& client);
    };
} // namespace server

#endif
