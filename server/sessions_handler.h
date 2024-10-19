#ifndef SERVER_SESSIONS_HANDLER_H
#define SERVER_SESSIONS_HANDLER_H

#include <memory>
#include <mutex>
#include <vector>

#include "common_queue.h"
#include "common_socket.h"
#include "server_session.h"

class SessionsHandler {
private:
    std::vector<std::shared_ptr<Session>> sessions;
    std::shared_ptr<Queue<ClientCommand>> recv_queue;
    std::mutex mtx;

public:
    explicit SessionsHandler(const std::shared_ptr<Queue<ClientCommand>>& recv_q);
    ~SessionsHandler();

    void broadcast(const ServerMessage& msg);
    void add(Socket& client);
    void remove_closed_sessions();
    void remove_all_sessions();
};

#endif  // SERVER_SESSIONS_HANDLER_H
