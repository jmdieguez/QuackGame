#ifndef SESSION_H
#define SESSION_H

#include <memory>

#include "../common/snapshots.h"
#include "../common/lobby_messages.h"
#include "client_command.h"
#include "../common/socket.h"
#include "receiver.h"
#include "sender.h"
#include "games_manager.h"
class GamesManager;
class Session
{
private:
    uint16_t id;
    bool finished;
    Socket socket;
    std::atomic<bool> is_playing;
    Sender sender;
    void check_close_socket();

public:
    Session(const uint16_t& id, Socket, GamesManager& game_manager);
    ~Session();
    void run();
    void stop();
    void send(const Snapshot &msg);
    bool has_finished() const;
};

#endif // SESSION_H
