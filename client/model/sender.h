#ifndef SENDER_H
#define SENDER_H

#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../common/thread.h"
#include "../../common/snapshots.h"
#include "../../common/client_actions.h"

#include "protocol.h"

class Sender : public Thread
{
private:
    ClientProtocol protocol;
    Queue<ClientIdAction> &queue_sender;
    bool closed = false;

public:
    explicit Sender(Socket &skt, Queue<ClientIdAction> &);
    ~Sender();
    void run() override;
    void stop() override;
};

#endif // SENDER_H
