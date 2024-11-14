#include "lobby.h"


Lobby::Lobby(ClientProtocol& protocol): protocol(protocol) {}

void Lobby::create_room(const std::string& name) {
     protocol.send_create_game(name);
}

void Lobby::join_room(const uint16_t& id) {
     protocol.send_join_game(id);
}

void Lobby::start_game() {
     protocol.send_start_game();
   //  uint16_t action;
   //  protocol.read_data(action);
   //  return action == 1;
}

void  Lobby::get_game_list(std::map<uint16_t, std::string>& games) {
    protocol.send_game_list();
    protocol.read_list(games);

}

Lobby::~Lobby() {}
