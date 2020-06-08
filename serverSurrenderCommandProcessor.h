#ifndef SURRENDER_COMMAND_PROCESSOR_H_
#define SURRENDER_COMMAND_PROCESSOR_H_
#include <string>
#include <mutex>
#include "./serverCommandProcessor.h"
#include "./serverClientConnection.h"


namespace server {
    class SurrenderCommandProcessor : public CommandProcessor {
        public:
        SurrenderCommandProcessor();
        ~SurrenderCommandProcessor();
        virtual std::string operator()(char command,
            server::ClientConnection& client);
    };
} // namespace server

#endif
