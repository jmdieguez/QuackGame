#include "acceptor.h"
#include <memory>
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
    matches.remove_all_matches();
}

void Acceptor::run()
{
    try
    {
        while (_keep_running.load())
        {
            Socket peer = socket.accept();
            uint16_t id = session_id++;
            sessions.emplace(id, std::make_shared<LobbySession>(id, peer, matches));
            sessions.at(id)->start();
            remove_disconnected_sessions();
            // matches.remove_finished_matches();
        }
    }
    catch (LibError &e)
    {
    }
}

void Acceptor::remove_disconnected_sessions() {
    for (auto it = sessions.begin(); it != sessions.end(); ) {
        auto session = it->second;
        if (!session || !session->is_alive()) {
            session->join();
            it = sessions.erase(it);
        } else {
            ++it;
        }
    }
}

void Acceptor::remove_all_sessions() {
    for (auto& [id, session] : sessions) {
        if (session->is_alive()) {
            session->stop();
        }
        session->join();
    }
    sessions.clear();
}
