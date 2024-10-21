#ifndef SERVER_RECEIVER_H
#define SERVER_RECEIVER_H

#include <memory>

#include "queue.h"
#include "socket.h"
#include "thread.h"
#include "protocol.h"

class Receiver: public Thread {
private:
    Socket& client;                                    // Socket compartido con Sender
    std::shared_ptr<Queue<ClientCommand>> recv_queue;  // Queue compartida con Server
    ServerProtocol protocol;
    bool closed;

public:
    Receiver(Socket& skt, const std::shared_ptr<Queue<ClientCommand>>& recv_q);
    ~Receiver();
    void run() override;
};

#endif  // SERVER_RECEIVER_H
