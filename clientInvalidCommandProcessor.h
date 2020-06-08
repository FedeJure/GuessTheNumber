#ifndef INVALID_COMMAND_PROCESSOR_H_
#define INVALID_COMMAND_PROCESSOR_H_
#include <string>
#include "./clientCommandProcessor.h"
#include "./client.h"


namespace client {
    class InvalidCommandProcessor : public CommandProcessor {
        public:
        InvalidCommandProcessor();
        ~InvalidCommandProcessor();
        virtual std::string operator()(std::string const command,
            client::Client& client);
    };
} // namespace client

#endif
