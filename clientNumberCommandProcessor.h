#ifndef NUMBER_COMMAND_PROCESSOR_H_
#define NUMBER_COMMAND_PROCESSOR_H_
#include <string>
#include "clientCommandProcessor.h"
#include "./client.h"


namespace client {
    class NumberCommandProcessor : public CommandProcessor {
        public:
        NumberCommandProcessor();
        ~NumberCommandProcessor();
        virtual std::string operator()(std::string const command,
            client::Client& client);
    };
} // namespace client

#endif
