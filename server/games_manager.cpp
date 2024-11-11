#include "monitor_games.h"

#include "games_manager.h"
GamesManager::GamesManager(): monitor(MonitorGames()) {}
Queue<ClientCommand>* GamesManager::handle_lobby(const ActionLobby& action, const uint16_t& session_id,
                                               Queue<Snapshot>& sender, ServerProtocol& protocol) {
    Queue<ClientCommand>* game_queue = nullptr;
    switch (action.type) {
        case ClientActionType::CREATE_GAME:
            monitor.create_game(session_id, sender, game_queue);
            break;
        case ClientActionType::JOIN_GAME:
            monitor.add_player(action.game_id, session_id, sender, game_queue);
            break;
        case ClientActionType::GAME_LIST:
            monitor.list_games(protocol);
            break;
        case ClientActionType::START_GAME:
            monitor.start_game(action.game_id, session_id);
            break;
        default:
          return game_queue; // no esta en ninguna partida, no es valido el codigo recibido
    }

    return game_queue;
}
