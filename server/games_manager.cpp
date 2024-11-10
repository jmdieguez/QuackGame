
#include "games_manager.h"


Queue<ClientCommand>* GamesManager::handle_lobby(const ActionLobby& action, const uint16_t& session_id,
                                               Queue<Snapshot>& sender, Queue<LobbyMessage>& lobby) {
    Queue<ClientCommand>* game_queue = nullptr;
    switch (action.type) {
        case ClientActionType::CREATE_GAME:
            create_game(session_id, sender);
            break;
        case ClientActionType::JOIN_GAME:
            add_player(action.game_id, session_id, sender);
            break;
        case ClientActionType::GAME_LIST:
            list_games(lobby);
            break;
        case ClientActionType::START_GAME:
            start_game(action.game_id, session_id);
            break;
        default:
          return nullptr; // no esta en ninguna partida, no es valido el codigo recibido
    }

    return game_queue;
}

void GamesManager::create_game(const uint16_t &creator_id, Queue<Snapshot>& queue) {
    std::lock_guard<std::mutex> lock(mtx);
    auto newGame = std::make_shared<Gameloop>(id_counter, creator_id);
    newGame->add_new_player(creator_id, queue);
    games[id_counter] = newGame;
    id_counter++;
}

void GamesManager::add_player(const uint16_t& game_id, const uint16_t &creator_id, Queue<Snapshot>& queue) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = games.find(game_id);
    if (it != games.end()) {
        it->second->add_new_player(creator_id, queue);
        player_to_game[creator_id] = game_id;
    }
}

void GamesManager::start_game(const uint16_t& game_id, const uint16_t &creator_id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = games.find(game_id);
    if (it != games.end()) {
        it->second->start_game(creator_id);
    }
}


void GamesManager::list_games(Queue<LobbyMessage>& queue) {
    std::lock_guard<std::mutex> lock(mtx);
    for (const auto& [id, gameloop_ptr] : games) {
        if (gameloop_ptr) {
            std::string name = gameloop_ptr->get_name();
            queue.push(LobbyMessage(name, id));
        }
    }
}

bool GamesManager::is_game_started(const uint16_t& session_id) {
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