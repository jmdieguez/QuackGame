#include "lobby.h"


Lobby::Lobby(ClientProtocol& protocol): protocol(protocol) {}

void Lobby::create_room(const std::string& name) {
     protocol.send_create_game(name);
}

void Lobby::join_room(const uint16_t& id) {
     protocol.send_join_game(id);
}

bool Lobby::start_game() {
     protocol.send_start_game();
     uint16_t action;
     protocol.read_data(action);
     return action == 1;
}

Lobby::~Lobby() {}
