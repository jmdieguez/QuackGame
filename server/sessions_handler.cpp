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
    sessions[id] = session;
}

void SessionsHandler::remove_closed_sessions()
{
    std::lock_guard<std::mutex> lock(mtx);
    for (auto it = sessions.begin(); it != sessions.end();)
    {
        if (it->second == nullptr || it->second->has_finished())
        {
            it = sessions.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void SessionsHandler::remove_all_sessions()
{
    std::lock_guard<std::mutex> lock(mtx);
    recv_queue->close();
    for (auto &[id, session] : sessions)
    {
        session->stop();
    }
    sessions.clear();
}

void SessionsHandler::broadcast(const Snapshot &msg)
{
    std::lock_guard<std::mutex> lock(mtx);
    if (msg.is_ended)
    {
        for (auto &[id, session] : sessions)
        {
            Snapshot personalized_msg = msg;
            personalized_msg.game_result =
                (id == msg.winner_id) ? GameResult::VICTORY : GameResult::DEFEAT;

            session->send(personalized_msg);
        }
    }
    else
    {
        for (auto &[id, session] : sessions)
        {
            session->send(msg);
        }
    }
}

bool SessionsHandler::has_clients()
{
    std::lock_guard<std::mutex> lock(mtx);
    return !sessions.empty();
    ;
}