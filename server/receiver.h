#ifndef SERVER_RECEIVER_H
#define SERVER_RECEIVER_H

#include <memory>

#include "../common/queue.h"
#include "../common/socket.h"
#include "../common/thread.h"
#include "client_command.h"
#include "protocol.h"

class Receiver: public Thread {
private:
    const uint16_t &session_id;
    Socket& client;                                    // Socket compartido con Sender
    std::shared_ptr<Queue<ClientCommand>> recv_queue;  // Queue compartida con Server
    ServerProtocol protocol;
    bool closed;

public:
    Receiver(Socket& skt, const std::shared_ptr<Queue<ClientCommand>>& recv_q, const uint16_t &id);
    ~Receiver();
    void run() override;
};

#endif  // SERVER_RECEIVER_H