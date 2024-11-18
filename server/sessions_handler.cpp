#include "sessions_handler.h"

#include <algorithm>
#include <sstream>
#include <utility>
#include "../common/liberror.h"

SessionsHandler::SessionsHandler(const std::shared_ptr<Queue<ClientCommand>> &recv_q) : recv_queue(recv_q) {}

SessionsHandler::~SessionsHandler() {}

void SessionsHandler::add(Socket &client, const uint16_t &id)
{
    std::lock_guard<std::mutex> lock(mtx);
    std::shared_ptr<Session> session = std::make_shared<Session>(client, recv_queue, id);
    session->run();
    sessions.emplace_back(session);
}

void SessionsHandler::remove_closed_sessions()
{
    std::lock_guard<std::mutex> lock(mtx);
    sessions.erase(std::remove_if(sessions.begin(), sessions.end(),
                                  [](const std::shared_ptr<Session> &session)
                                  {
                                      return session == nullptr || session->has_finished();
                                  }),
                   sessions.end());
}

void SessionsHandler::remove_all_sessions()
{
    std::lock_guard<std::mutex> lock(mtx);
    recv_queue->close();
    for (auto &session : sessions) {
        session->stop();
    }
}

void SessionsHandler::broadcast(const Snapshot &msg)
{
    std::lock_guard<std::mutex> lock(mtx);
    for (auto &session : sessions)
        session->send(msg);
}

bool SessionsHandler::has_clients() {
    std::lock_guard<std::mutex> lock(mtx);
    return (sessions.size() > 0); 
}