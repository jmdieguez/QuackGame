#ifndef SERVER_RECEIVER_H
#define SERVER_RECEIVER_H

#include <memory>

#include "../common/queue.h"
#include "../common/socket.h"
#include "../common/thread.h"
#include "../common/actions.h"
#include "protocol.h"

class Receiver: public Thread {
private:
    Socket& client;                                    // Socket compartido con Sender
    std::shared_ptr<Queue<ActionMessage>> recv_queue;  // Queue compartida con Server
    ServerProtocol protocol;
    bool closed;

public:
    Receiver(Socket& skt, const std::shared_ptr<Queue<ActionMessage>>& recv_q);
    ~Receiver();
    void run() override;
};

#endif  // SERVER_RECEIVER_H
