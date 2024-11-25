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

class MonitorGames {
private:
    std::mutex mtx;
    std::map<uint16_t, std::shared_ptr<Gameloop>> games;
    uint16_t id_counter = 0;
public:
    MonitorGames();

    uint16_t create_game(const uint16_t &creator_id, const std::string &name);
    void join_game(const uint16_t &player_id, const uint16_t &game_id, Socket &skt);
    std::vector<LobbyMessage> list_games();
    void start_game(const uint16_t &creator_id, const int &game_id, Socket &skt);
    void remove_finished_matches();
    void remove_all_matches();
    void number_of_players(const uint16_t& game_id, uint16_t& amount_of_players);
};


#endif // MONITOR_GAMES_H
