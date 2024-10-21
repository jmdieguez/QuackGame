#ifndef SERVER_SENDER_H
#define SERVER_SENDER_H

#include "queue.h"
#include "socket.h"
#include "thread.h"
#include "protocol.h"

class ServerMessage;

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
