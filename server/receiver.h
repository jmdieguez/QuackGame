#ifndef SERVER_RECEIVER_H
#define SERVER_RECEIVER_H

#include <memory>

#include "common_client_command.h"
#include "common_queue.h"
#include "common_socket.h"
#include "common_thread.h"
#include "server_protocol.h"

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
