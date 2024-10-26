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

class SessionsHandler {
private:
    std::vector<std::shared_ptr<Session>> sessions;
    std::shared_ptr<Queue<ClientCommand>> recv_queue;
    std::mutex mtx;
    uint16_t current_id = 0; // Contador de clientes
public:
    explicit SessionsHandler(const std::shared_ptr<Queue<ClientCommand>>& recv_q);
    ~SessionsHandler();

    void broadcast(const Snapshot& msg);
    void add(Socket& client);
    void remove_closed_sessions();
    void remove_all_sessions();
};

#endif  // SERVER_SESSIONS_HANDLER_H
