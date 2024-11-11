

#include "monitor_games.h"

void MonitorGames::create_game(const uint16_t &creator_id, Queue<Snapshot>& queue, Queue<ClientCommand>* game_queue) {
    std::lock_guard<std::mutex> lock(mtx);
    auto newGame = std::make_shared<Gameloop>(id_counter, creator_id);
    newGame->add_new_player(creator_id, queue, game_queue);
    games[id_counter] = newGame;
    id_counter++;
}

void MonitorGames::add_player(const uint16_t& game_id, const uint16_t &creator_id, Queue<Snapshot>& queue, Queue<ClientCommand>* game_queue) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = games.find(game_id);
    if (it != games.end()) {
        it->second->add_new_player(creator_id, queue, game_queue);
        player_to_game[creator_id] = game_id;
    }
}

void MonitorGames::start_game(const uint16_t& game_id, const uint16_t &creator_id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = games.find(game_id);
    if (it != games.end()) {
        it->second->start_game(creator_id);
    }
}


void MonitorGames::list_games(ServerProtocol& protocol) {
    std::lock_guard<std::mutex> lock(mtx);
    Queue<LobbyMessage> queue;
    for (const auto& [id, gameloop_ptr] : games) {
        if (gameloop_ptr) {
            std::string name = gameloop_ptr->get_name();
            protocol.send_lobby_info(LobbyMessage(name, id));
        }
    }

}

bool MonitorGames::is_game_started(const uint16_t& session_id) {
    std::lock_guard<std::mutex> lock(mtx);
    std::atomic<bool> state = false;
    auto player_it = player_to_game.find(session_id);
    if (player_it == player_to_game.end()) {
        return state;
    }

    uint16_t game_id = player_it->second;

    auto game_it = games.find(game_id);
    if (game_it != games.end()) {
        game_it->second->game_state(state);
        return state;
    }

    return state;
}