
#ifndef LOBBY_MESSAGE_H
#define LOBBY_MESSAGE_H

#include <string>
#include <cstdint>
#include "defs.h"
#include "client_actions.h"

class LobbyMessage {
public:
    uint16_t game_id;
    std::string name;

    LobbyMessage(const std::string& info, const uint16_t& id)
        : game_id(id), name(info) {}

};

class ActionLobby {
public:
    ClientActionType type;
    uint16_t game_id;
    std::string game_name;

    ActionLobby(const ClientActionType &t, const uint16_t& game_id = 0)
        : type(t), game_id(game_id), game_name("") {}

    ActionLobby() : type(ClientActionType::UNDEFINED), game_id(0), game_name("") {}

    ~ActionLobby() {}
};
#endif //LOBBY_MESSAGE_H
