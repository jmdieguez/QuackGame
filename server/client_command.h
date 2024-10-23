#ifndef SERVER_CLIENT_COMMAND_H
#define SERVER_CLIENT_COMMAND_H

#include <cstdint>

#include "../common/client_actions.h"

class ClientCommand {
public:
    uint8_t player_id;
    ActionMessage message;

    ClientCommand(const uint8_t &id, const ActionMessage &msg) : player_id(id), message(msg) {}
    ClientCommand() : player_id(0) {}
};

#endif // SERVER_CLIENT_COMMAND_H
