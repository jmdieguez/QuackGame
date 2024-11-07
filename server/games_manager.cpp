
#include "games_manager.h"
#include "../common/lobby_message.h"


Queue<ClientCommand>* GamesManager::handle_lobby(const ActionLobby& action, const uint16_t& session_id,
                                                 Queue<Snapshot>& sender, Queue<LobbyMessages>& lobby) {
    Queue<ClientCommand>* game_queue;
    switch (action.type) {
        case ClientActionType::CREATE_GAME:
            create_game(session_id, queue);
            break;
        case ClientActionType::JOIN_GAME:
            add_player(action.game_id, session_id, queue);
            break;
        case ClientActionType::GAME_LIST:
            list_games(lobby);
            break;
        case ClientActionType::START_GAME:
            start_game(action.game_id, session_id);
        default:
          return nullptr; // no esta en ninguna partida, no es valido el codigo recibido
    }

    return game_queue;
}

void GamesManager::create_game(const uint16_t &creator_id, Queue<Message>& queue) {
    auto newGame = std::make_shared<Gameloop>(id_counter, creator_id);
    newGame->add_new_player(creator_id, queue);
    games[id_counter] = newGame;
    id_counter++;
}

void GamesManager::add_player(const uint16_t& game_id, const uint16_t &creator_id, Queue<Snapshot>& queue) {
    auto it = games.find(game_id);
    if (it != games.end()) {
        it->second->add_new_player(creator_id, queue);
    }
}

void GamesManager::start_game(const uint16_t& game_id, const uint16_t &creator_id) {
    auto it = games.find(game_id);
    if (it != games.end()) {
        it->second->start_game(creator_id);
    }
}


void GamesManager::list_games(Queue<LobbyMessages>& queue) {
    for (const auto& [id, gameloop_ptr] : games) {
        if (gameloop_ptr) {
            std::string name = gameloop_ptr->get_name();
            queue.push(LobbyMessage(name, id));
        }
    }
}