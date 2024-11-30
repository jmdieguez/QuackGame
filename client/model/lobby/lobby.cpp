#include "lobby.h"

Lobby::Lobby(ClientProtocol &protocol) : protocol(protocol) {}

std::vector<UserLobbyInfo> Lobby::create_room(const std::string &name)
{
    protocol.send_create_game(2, name);
    return protocol.read_create_game_info();
}

void Lobby::join_room(const uint16_t &id)
{
    protocol.send_join_game(id, 1);
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
