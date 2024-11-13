

#include "monitor_games.h"
MonitorGames::MonitorGames() {
}

Queue<ClientCommand>* MonitorGames::create_game(const uint16_t &creator_id, const std::string& name, Queue<Snapshot>& queue) {
  // TODO: Chequear que no existe una partida con mismo nombre
    std::lock_guard<std::mutex> lock(mtx);
    Queue<ClientCommand>* game_queue = nullptr;
    auto newGame = std::make_shared<Gameloop>(id_counter, name, creator_id);
    game_queue = newGame->add_new_player(creator_id, queue);
    games[id_counter] = newGame;
    id_counter++;
    return game_queue;
}

Queue<ClientCommand>* MonitorGames::add_player(const uint16_t& game_id, const uint16_t &creator_id, Queue<Snapshot>& queue) {
    std::lock_guard<std::mutex> lock(mtx);
    Queue<ClientCommand>* game_queue = nullptr;
    auto it = games.find(game_id);
    if (it != games.end()) {
        game_queue = it->second->add_new_player(creator_id, queue);
        player_to_game[creator_id] = game_id;
    }
    return game_queue;
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