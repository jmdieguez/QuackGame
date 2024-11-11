#ifndef SERVER_SESSIONS_HANDLER_H
#define SERVER_SESSIONS_HANDLER_H

#include <memory>
#include <mutex>
#include <vector>

#include "../common/queue.h"
#include "../common/socket.h"
#include "session.h"
#include "client_command.h"

class SessionsHandler {
private:
    std::list<std::pair<Queue<Snapshot>&, uint16_t>> clients_queues;
    std::mutex mtx;
public:
    SessionsHandler();
    ~SessionsHandler();

    void broadcast(const Snapshot& msg);
    void add(Queue<Snapshot>& queue, uint16_t id);
    void remove_closed_sessions();
    void remove_all_sessions();
    void remove_client(const uint16_t&);
};

#endif  // SERVER_SESSIONS_HANDLER_H
