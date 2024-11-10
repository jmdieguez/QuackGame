#include "session.h"

#include <utility>

Session::Session(const uint16_t& id, Socket client, GamesManager& game_manager):
    manager(game_manager),
    id(id), finished(false), socket(std::move(client)), sender_queue(100), lobby_queue(100), is_playing(false),
    sender(socket, id, sender_queue, lobby_queue, is_playing),
    receiver(socket, id, manager, sender_queue, lobby_queue, is_playing) {}

Session::~Session() {}

void Session::check_close_socket()
{
    if (!receiver.is_alive() || !sender.is_alive())
        return;
    socket.shutdown(2);
    socket.close();
}

void Session::run()
{
    receiver.start();
    sender.start();
}

void Session::stop()
{
    finished = true;
    receiver.stop();
    sender.stop();
    check_close_socket();
    sender.join();
    receiver.join();
}

void Session::send(const Snapshot &msg) { sender.send(msg); }

bool Session::has_finished() const { return finished; }
