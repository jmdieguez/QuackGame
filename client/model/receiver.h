#ifndef SERVER_RECEIVER_H
#define SERVER_RECEIVER_H

#include <memory>

#include "../common/queue.h"
#include "../common/socket.h"
#include "../common/thread.h"
#include "../common/snapshots.h"
#include "protocol.h"

class Receiver: public Thread {
private:
    ClientProtocol protocol;
    Queue<Snapshot>& recv_queue;

public:
    explicit Receiver(Socket& skt, Queue<Snapshot>& recv_q);
    ~Receiver();
    void run() override;
    void stop() override;
};

#endif  // SERVER_RECEIVER_H
