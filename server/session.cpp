#include "session.h"

#include <utility>

Session::Session(const uint16_t& id, Socket client, GamesManager& game_manager):
    id(id), finished(false), socket(std::move(client)),
    sender(socket, id, game_manager) {}

Session::~Session() {}

void Session::check_close_socket()
{
    if (!sender.is_alive())
        return;
    socket.shutdown(2);
    socket.close();
}

void Session::run()
{
    sender.start();
}

void Session::stop()
{
    finished = true;
    sender.stop();
    check_close_socket();
    sender.join();
}

void Session::send(const Snapshot &msg) { sender.send(msg); }

bool Session::has_finished() const { return finished; }
