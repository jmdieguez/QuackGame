#include "sender.h"
#include "../../common/liberror.h"
#include "protocol.h"
#include <cstdint>

Sender::Sender(Socket &skt, Queue<ClientIdAction> &queue) : protocol(skt), queue_sender(queue), closed(false) {}

void Sender::run()
{
    try
    {
        while (!closed && _keep_running)
        {
            ClientIdAction action = queue_sender.pop();
            protocol.send_id_action(action, closed);
        }
    }
    catch (LibError &e)
    {
    }
    catch (ClosedQueue &e)
    {
    }
}

void Sender::stop()
{
    _keep_running = false;
    queue_sender.close();
}

Sender::~Sender() {}