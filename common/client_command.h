#ifndef CLIENT_COMMAND_H
#define CLIENT_COMMAND_H

#include "client_command_type.h"
#include <string>

class ClientCommand {
public:
    const ClientCommandType type;
    const std::string opt_message;

    ClientCommand(const ClientCommandType &t, const std::string &m) : type(t), opt_message(m) {}
    ~ClientCommand() {}
};

#endif // CLIENT_COMMAND_H
