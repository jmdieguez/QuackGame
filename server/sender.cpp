#include "sender.h"

#include "../common/liberror.h"
#include "protocol.h"

Sender::Sender(Socket &skt, const uint16_t &id) : session_id(id), protocol(skt) {}

void Sender::run()
{
    try
    {
        while (!closed && _keep_running)
        {
            Snapshot message = out_queue.pop();
            if (!closed && _keep_running)
                protocol.send_snapshot(message);
        }
    }
    catch (LibError &e)
    {
        _keep_running = false;
    }
    catch (ClosedQueue &e)
    {
        _keep_running = false;
    }
}

void Sender::send(const Snapshot &snapshot)
{
    out_queue.push(snapshot);
}

void Sender::stop() { out_queue.close(); }

Sender::~Sender() {}
