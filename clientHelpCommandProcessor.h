#ifndef HELP_COMMAND_PROCESSOR_H_
#define HELP_COMMAND_PROCESSOR_H_
#include <string>
#include "./clientCommandProcessor.h"
#include "./client.h"


namespace client {
    class HelpCommandProcessor : public CommandProcessor {
        public:
        HelpCommandProcessor();
        ~HelpCommandProcessor();
        virtual std::string operator()(std::string const command,
            client::Client& client);
    };
} // namespace client

#endif
