#ifndef GAMES_MANAGER_H
#define GAMES_MANAGER_H

#include "gameloop.h"
#include "client_command.h"
#include <mutex>
#include <map>
#include <memory>
#include <cstdint>
#include "../common/snapshots.h"
#include "../common/lobby_messages.h"

class GamesManager {
private:
  std::mutex mtx;
  std::map<uint16_t, std::shared_ptr<Gameloop>> games;
  std::map<uint16_t, uint16_t> player_to_game;
  uint16_t id_counter = 0;
  void create_game(const uint16_t &creator_id, Queue<Snapshot>&);
  void add_player(const uint16_t&, const uint16_t &, Queue<Snapshot>&);
  void start_game(const uint16_t&, const uint16_t &);
  void list_games(Queue<LobbyMessage>&);
public:
    Queue<ClientCommand>* handle_lobby(const ActionLobby& action, const uint16_t& session_id,
                                                Queue<Snapshot>& sender, Queue<LobbyMessage>& lobby);
   bool is_game_started(const uint16_t& session_id);
};



#endif //GAMES_MANAGER_H
