#ifndef SURRENDER_COMMAND_PROCESSOR_H_
#define SURRENDER_COMMAND_PROCESSOR_H_
#include <string>
#include "./clientCommandProcessor.h"
#include "./client.h"


namespace client {
    class SurrenderCommandProcessor : public CommandProcessor {
        public:
        SurrenderCommandProcessor();
        ~SurrenderCommandProcessor();
        virtual std::string operator()(std::string const command,
            client::Client& client);
    };
} // namespace client

#endif
