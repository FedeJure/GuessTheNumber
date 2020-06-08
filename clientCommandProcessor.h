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
        virtual ~CommandProcessor() {}
    };
} // namespace client

#endif
