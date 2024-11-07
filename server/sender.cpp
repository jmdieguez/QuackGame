#include "sender.h"

#include "../common/liberror.h"
#include "protocol.h"

Sender::Sender(Socket& skt, const uint16_t &id, Queue<Snapshot>& queue, Queue<LobbyMessage>& l, std::atomic<bool>& playing):
    session_id(id), protocol(skt), out_queue(queue), lobby_queue(l), is_playing(playing) {}

void Sender::run()
{
    try
    {
        while (!closed && _keep_running)
        {
            if (!is_playing) {
                LobbyMessage lobby = lobby_queue.pop();
                protocol.send_lobby_info(lobby);
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

void Sender::send(const Snapshot &snapshot)
{
    out_queue.push(snapshot);
}

void Sender::stop() { out_queue.close(); }

Sender::~Sender() {}