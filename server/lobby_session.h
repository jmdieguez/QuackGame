#ifndef LOBBY_SESSION_H
#define LOBBY_SESSION_H

#include "../common/thread.h"
#include "../common/socket.h"
#include "monitor_games.h"

class LobbySession : public Thread {
private:
    int game_joined = -1;
    const uint16_t id;
    Socket socket;
    MonitorGames &matches;
public:
    LobbySession(const uint16_t &i, Socket& skt, MonitorGames &m);
    ~LobbySession();
    void run() override;
    void stop() override;
};

#endif // LOBBY_SESSION_H
