#include "sessions_handler.h"

#include <algorithm>
#include <sstream>
#include <utility>

SessionsHandler::SessionsHandler(const std::shared_ptr<Queue<ClientCommand>>& recv_q):
        recv_queue(recv_q) {}

SessionsHandler::~SessionsHandler() {}

void SessionsHandler::add(Socket& client) {
    std::lock_guard<std::mutex> lock(mtx);
    // Crear un generador de id's thread-safe
    // Asignarle el id a la sesión, y que esta se guarde también en el receiver (para identificarlo)
    std::shared_ptr<Session> session = std::make_shared<Session>(std::move(client), recv_queue);
    session->run();
    sessions.emplace_back(session);
}

void SessionsHandler::remove_closed_sessions() {
    std::lock_guard<std::mutex> lock(mtx);
    sessions.erase(std::remove_if(sessions.begin(), sessions.end(),
                                  [](const std::shared_ptr<Session>& session) {
                                      return session == nullptr || session->has_finished();
                                  }),
                   sessions.end());
}

void SessionsHandler::remove_all_sessions() {
    std::lock_guard<std::mutex> lock(mtx);
    recv_queue->close();
    for (auto& session: sessions) {
        session->stop();
    }
}

void SessionsHandler::broadcast(const ServerMessage& msg) {
    std::lock_guard<std::mutex> lock(mtx);

    for (auto& session: sessions) {
        // session->send(msg);
    }
}
