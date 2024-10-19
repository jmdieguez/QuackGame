#ifndef COMMON_SERVER_MESSAGE_H
#define COMMON_SERVER_MESSAGE_H

#include <string>

#include "common_reward_id.h"

#define SERVER_MSG_CODE 6
#define BOX_RESPAWNED 5
#define BOX_TAKEN 4

class ServerMessage {
public:
    const uint8_t code;
    const uint8_t action;  // BOX_RESPAWNED o BOX_TAKEN
    const std::string name;
    const uint16_t name_len;
    const RewardID reward_id;

    ServerMessage(const std::string& n, const uint16_t& l, const RewardID& id):
            code(SERVER_MSG_CODE), action(BOX_TAKEN), name(n), name_len(l), reward_id(id) {}

    ServerMessage():
            code(SERVER_MSG_CODE),
            action(BOX_RESPAWNED),
            name("Undefined"),
            name_len(0),
            reward_id(RewardID::Undefined) {}

    ~ServerMessage() {}
};

#endif  // COMMON_CLIENT_COMMAND_H
