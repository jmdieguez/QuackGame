#include "lobby.h"

#define MULTIPLAYER 2
#define SINGLEPLAYER 1

Lobby::Lobby(ClientProtocol &protocol) : protocol(protocol) {}

std::vector<UserLobbyInfo> Lobby::create_room(const std::string &name)
{
    protocol.send_create_game(game_mode, name);
    users = protocol.read_users_info();
    return users;
}

std::vector<UserLobbyInfo> Lobby::get_users()
{
    return users;
}

void Lobby::join_room(const uint16_t& id)
{
    protocol.send_join_game(id, game_mode);
    users = protocol.read_users_info();

}

void Lobby::select_game(const uint16_t &id)
{
    game_id = id;
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

void Lobby::prepare_multiplayer_game() {
    game_mode = MULTIPLAYER;
}
void Lobby::prepare_single_player_game() {
    game_mode = SINGLEPLAYER;
}

Lobby::~Lobby() {}
