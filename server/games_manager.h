#ifndef GAMES_MANAGER_H
#define GAMES_MANAGER_H

#include "client_command.h"
#include <mutex>
#include <map>
#include <memory>
#include <cstdint>
#include "monitor_games.h"
#include "../common/snapshots.h"
#include "../common/lobby_messages.h"
#include "../common/queue.h"
#include "protocol.h"

class GamesManager {
private:
    MonitorGames monitor;
public:
    GamesManager();
    Queue<ClientCommand>* handle_lobby(const ActionLobby& action, const uint16_t& session_id,
                                                Queue<Snapshot>& sender, Queue<LobbyMessage>& queue, uint16_t& game_size);
};

#endif //GAMES_MANAGER_H
