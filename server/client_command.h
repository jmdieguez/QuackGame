#ifndef SERVER_CLIENT_COMMAND_H
#define SERVER_CLIENT_COMMAND_H

#include <cstdint>

#include "../common/client_actions.h"

class ClientCommand
{
public:
    uint16_t session_id;
    uint16_t player_id;
    ActionMessage message;

    ClientCommand(const uint16_t &id, const ActionMessage &msg) : session_id(id), player_id(msg.id), message(msg) {}
    ClientCommand() : player_id(0) {}
};

#endif // SERVER_CLIENT_COMMAND_H
