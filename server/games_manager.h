
#ifndef GAMES_MANAGER_H
#define GAMES_MANAGER_H

#include "../client_command.h"
#include <cstdint>
#include "gameloop.h"
#include "../common/snapshots.h"
#include "../common/message.h"

class GamesManager {
private:
  std::map<uint16_t, std::shared_ptr<Gameloop>> games;
  uint16_t id_counter = 0;
  void create_game(const uint16_t &creator_id, Queue<LobbyMessage>&);
  void add_player(const uint16_t&, const uint16_t &, Queue<Snapshot>&);
  void start_game(const uint16_t&, const uint16_t &);
  void list_games(Queue<LobbyMessage>&);
public:
   Queue<ClientCommand>* handle_lobby(const ActionLobby&, const uint16_t&, Queue<LobbyMessage>&);
};



#endif //GAMES_MANAGER_H
