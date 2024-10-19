#ifndef SERVER_SENDER_H
#define SERVER_SENDER_H

#include "common_queue.h"
#include "common_server_message.h"
#include "common_socket.h"
#include "common_thread.h"
#include "server_protocol.h"

class Sender: public Thread {
private:
    bool closed = false;
    Socket& client;  // Socket compartido con Receiver
    Queue<ServerMessage> out_queue;
    ServerProtocol protocol;

public:
    explicit Sender(Socket& skt);
    ~Sender();
    void run() override;
    void stop() override;
    void send(const ServerMessage& msg);
};

#endif  // SERVER_SENDER_H
