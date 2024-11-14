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

class Session {
public:
    const uint16_t id;
    Session(Socket &&client, const uint16_t &s_id, GamesManager& game_manager);
    ~Session();
    void run();
    void stop();
    void send(const Snapshot &msg);
    bool has_finished() const;

private:
    bool finished;
    Socket socket;
    Sender sender;
    void check_close_socket();
};

#endif // SESSION_H
