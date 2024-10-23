#include "../../common/thread.h"
#include "network.h"

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

bool Network::send_message()
{
    std::vector<uint8_t> message;
  //  queue_sender.try_pop(message);
    // message_serialized = protocol(message);
    // socket.send(message_serialized);
    return true;
}

void Network::sender_message()
{
    try
    {
        while (_keep_running && send_message())
        {
        }
    }
    catch (const ClosedQueue &err)
    {
    }
    catch (...)
    {
        std::cerr << "Unexpected error" << std::endl;
    }
}

bool Network::receive_message()
{
    uint8_t amount;
    if (protocol.read(amount)) {
       return false;
    }
    Snapshot snap;
    for (uint8_t i = 0; i <  amount; i++) {
        // receive duck information
        Duck newDuck;
        protocol.readDuck(newDuck);
        snap.ducks.push_back(newDuck);
    }
    queue_receiver.push(snap);
    return true;
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Network::Network(std::atomic<bool> &keep_running, Queue<Snapshot> &queue_receiver, Queue<ActionMessage> &queue_sender)
    : keep_running(keep_running), queue_receiver(queue_receiver), queue_sender(queue_sender)
{
}

void Network::run()
{
    std::thread sender_thread(&Network::sender_message, this);
    try
    {
        while (_keep_running && receive_message())
        {
        }
    }
    catch (const std::exception &err)
    {
    }
    catch (...)
    {
        std::cerr << "Unexpected error" << std::endl;
    }
    _is_alive = false;
    queue_sender.close();
    queue_receiver.close();
    keep_running = false;
    sender_thread.join();
}

Network::~Network()
{
    join();
}
