#ifndef SERVER_SESSIONS_HANDLER_H
#define SERVER_SESSIONS_HANDLER_H

#include <memory>
#include <mutex>
#include <vector>

#include "../common/server_message.h"
#include "../common/queue.h"
#include "../common/socket.h"
#include "session.h"
#include "client_command.h"
#include "games_manager.h"

class SessionsHandler {
private:
    std::list<std::pair<Queue<Snapshot>&, uint8_t>> clientsQueues;
    std::mutex mtx;
public:
    SessionsHandler();
    ~SessionsHandler();

    void broadcast(const Snapshot& msg);
    void add(const uint16_t&, Queue<Snapshot>&);
    void remove_closed_sessions();
    void remove_all_sessions();
};

#endif  // SERVER_SESSIONS_HANDLER_H
