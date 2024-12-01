#include "lobby.h"

Lobby::Lobby(ClientProtocol &protocol) : protocol(protocol) {}

std::vector<UserLobbyInfo> Lobby::create_room(const std::string &name)
{
    protocol.send_create_game(2, name);
    users = protocol.read_users_info();
    return users;
}

std::vector<UserLobbyInfo> Lobby::get_users()
{
    return users;
}

std::vector<UserLobbyInfo> Lobby::join_room(const uint16_t &id)
{
    protocol.send_join_game(id, 2);
    users = protocol.read_users_info();
    return users;
}

void Lobby::start_game(bool &start)
{
    protocol.send_start_game();
    ClientActionType action;
    protocol.read_start_game(action);
    start = action == ClientActionType::READY;
}

void Lobby::get_game_list(std::map<uint16_t, std::string> &games)
{
    protocol.send_game_list();
    protocol.read_list(games);
}

Lobby::~Lobby() {}
