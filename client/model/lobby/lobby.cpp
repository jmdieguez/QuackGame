#include "lobby.h"


Lobby::Lobby(ClientProtocol& protocol): protocol(protocol) {}

void Lobby::create_room(const std::string& name) {
     protocol.send_create_game(name);
}

void Lobby::join_room(const uint16_t& id) {
     protocol.send_join_game(id);
}

void Lobby::start_game(bool& start) {
     protocol.send_start_game();
     ClientActionType action;
     protocol.read_start_game(action);
     start = action == ClientActionType::READY;
}

void Lobby::get_game_list(std::map<uint16_t, std::string>& games) {
    protocol.send_game_list();
    protocol.read_list(games);

}

Lobby::~Lobby() {}
