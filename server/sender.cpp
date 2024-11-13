#include "sender.h"

#include "../common/liberror.h"
#include "protocol.h"

Sender::Sender(Socket& skt, const uint16_t &id, GamesManager& game_manager):
    session_id(id), protocol(skt), out_queue(1000), manager(game_manager), is_playing(false),
    receiver(skt, id, out_queue, is_playing) {}

void Sender::run()
{
    try
    {
        while (!closed && _keep_running)
        {
             if (!is_playing) {
                ActionLobby action = protocol.read_lobby();
                receiver_queue = manager.handle_lobby(action, session_id, out_queue, protocol);
                if (receiver_queue != nullptr) {
                    is_playing = true;
                    start_receiver();
                }
             } else {
                Snapshot message = out_queue.pop();
                protocol.send_snapshot(message);
             }
        }
    }
    catch (LibError &e)
    {
    }
    catch (ClosedQueue &e)
    {
    }
    _is_alive = false;
}

void Sender::start_receiver() {
   receiver.add_game_queue(receiver_queue);
   receiver.start();
}

void Sender::send(const Snapshot &snapshot)
{
    out_queue.push(snapshot);
}

void Sender::stop() { out_queue.close(); }


Sender::~Sender() {}