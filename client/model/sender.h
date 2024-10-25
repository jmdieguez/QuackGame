#ifndef SERVER_SENDER_H
#define SERVER_SENDER_H

#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../common/thread.h"
#include "../common/snapshots.h"
#include "../common/client_actions.h"

#include "protocol.h"

class Sender : public Thread {
private:
    ClientProtocol protocol;
    Queue<ClientActionType>&  queue_sender;
    bool closed = false;

public:
    explicit Sender(Socket& skt, Queue<ClientActionType>&);
    ~Sender();
    void run() override;
    void stop() override;
    void send(const Snapshot& msg);
};

#endif  // SERVER_SENDER_H
