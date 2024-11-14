#include "acceptor.h"

#include <memory>
#include "games_manager.h"
#include "../common/liberror.h"

Acceptor::Acceptor(const char *port) :
    socket(port), session_id(0) {}

Acceptor::~Acceptor() {}

void Acceptor::stop()
{
    _keep_running = false;
    socket.shutdown(2);
    socket.close();
    remove_all_sessions();
}

void Acceptor::run()
{
    try
    {
        GamesManager manager;
        while (_keep_running.load())
        {
            Socket peer = socket.accept();
            uint16_t id = session_id++;
            auto client = std::make_unique<Session>(std::move(peer), id, manager);
            client->run();
            sessions.push_back(std::move(client));
            remove_disconnected_sessions();
        }
    }
    catch (LibError &e)
    {
    }
}

void Acceptor::remove_disconnected_sessions() {
    sessions.remove_if([this](const std::unique_ptr<Session>& session) {
        return session == nullptr || session->has_finished();
    });
}

void Acceptor::remove_all_sessions() {
    for (auto& session: sessions) {
        session->stop();
    }
    sessions.clear();
}
