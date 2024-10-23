#ifndef SERVER_SENDER_H
#define SERVER_SENDER_H

#include "../common/queue.h"
#include "../common/socket.h"
#include "../common/thread.h"
#include "../common/snapshots.h"
#include "protocol.h"

class Sender: public Thread {
private:
    ServerProtocol protocol;
    bool closed = false;
    Queue<Snapshot> out_queue;

public:
    explicit Sender(Socket& skt);
    ~Sender();
    void run() override;
    void stop() override;
    void send(const Snapshot& msg);
};

#endif  // SERVER_SENDER_H
