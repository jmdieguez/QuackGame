
#ifndef MONITOR_GAMES_H
#define MONITOR_GAMES_H
#include "client_command.h"
#include <mutex>
#include <map>
#include <memory>
#include <cstdint>
#include "../common/snapshots.h"
#include "../common/lobby_messages.h"
#include "../common/queue.h"
#include "gameloop.h"
#include "protocol.h"

class MonitorGames {
private:
    std::mutex mtx;
    std::map<uint16_t, std::shared_ptr<Gameloop>> games;
    std::map<uint16_t, uint16_t> player_to_game;
    uint16_t id_counter = 0;
public:
    MonitorGames();
    Queue<ClientCommand>* create_game(const uint16_t &creator_id, Queue<Snapshot>&);
    Queue<ClientCommand>* add_player(const uint16_t&, const uint16_t &, Queue<Snapshot>&);
    void start_game(const uint16_t&, const uint16_t &);
    void list_games(ServerProtocol& protocol);
    bool is_game_started(const uint16_t&);
};


#endif //MONITOR_GAMES_H
