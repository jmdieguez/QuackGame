

#include "games_manager.h"
GamesManager::GamesManager(): monitor(MonitorGames()) {}
Queue<ClientCommand>* GamesManager::handle_lobby(const ActionLobby& action, const uint16_t& session_id,
                                               Queue<Snapshot>& sender, Queue<LobbyMessage>& lobby, uint16_t& game_size) {
    Queue<ClientCommand>* game_queue = nullptr;
    switch (action.type) {
        case ClientActionType::CREATE_GAME:
            monitor.create_game(session_id, action.game_name, sender);
            break;
        case ClientActionType::JOIN_GAME:
            std::cout << action.game_id << std::endl;
            game_queue = monitor.add_player(action.game_id, session_id, sender);
            break;
        case ClientActionType::GAME_LIST:
            monitor.list_games(lobby, game_size);
            break;
        case ClientActionType::START_GAME:
            game_queue = monitor.start_game(session_id);
            break;
        default:
          return game_queue; // no esta en ninguna partida, no es valido el codigo recibido
    }

    return game_queue;
}
