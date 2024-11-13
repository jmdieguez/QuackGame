#include "receiver.h"
#include "protocol.h"
#include "../common/liberror.h"
#include "client_command.h"

Receiver::Receiver(Socket &skt, const uint16_t &id, Queue<Snapshot>& queue,  std::atomic<bool>& playing):
    session_id(id), client(skt), sender_queue(queue), game_queue(nullptr), protocol(skt), closed(false), is_playing(playing) {}

Receiver::~Receiver() {}

void Receiver::run()
{
    try
    {
        while (!closed && _keep_running && game_queue != nullptr)
        {
            if (!closed) {
                ActionMessage message = protocol.read_action();
                ClientCommand command(session_id, message);
                game_queue->push(command);
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

void Receiver::add_game_queue(Queue<ClientCommand>* queue) {
  game_queue = queue;
}
