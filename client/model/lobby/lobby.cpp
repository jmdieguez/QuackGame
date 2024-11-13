#include "lobby.h"


Lobby::Lobby(ClientProtocol& protocol): protocol(protocol) {}

void Lobby::createRoom(const std::string& name) {
     protocol.send_create_game(name);
}

void Lobby::joinRoom(const uint16_t& id) {
     protocol.send_join_game(id);
}

Lobby::~Lobby() {}
