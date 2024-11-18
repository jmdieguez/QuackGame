
#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <memory>
#include <map>
#include "../common/socket.h"
#include "../common/thread.h"
#include "session.h"
#include "monitor_games.h"
#include "lobby_session.h"

class Acceptor : public Thread {
private:
    Socket socket;
    uint16_t session_id;
    MonitorGames matches;
    std::map<uint16_t, std::shared_ptr<LobbySession>> sessions;
    void remove_all_sessions();
    void remove_disconnected_sessions();
public:
    explicit Acceptor(const char* port);
    virtual ~Acceptor();
    void stop() override;
    void run() override;
};

#endif  // ACCEPTOR_H
