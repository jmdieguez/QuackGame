#include "session.h"

#include <utility>

Session::Session(Socket &&client, std::shared_ptr<Queue<ClientCommand>> &recv_q, const uint16_t &i) : id(i), socket(std::move(client)), sender(socket, id), receiver(socket, recv_q, id) {}

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
