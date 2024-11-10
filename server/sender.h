#ifndef SERVER_SENDER_H
#define SERVER_SENDER_H

#include "../common/queue.h"
#include "../common/socket.h"
#include "../common/thread.h"
#include "../common/snapshots.h"
#include "../common/lobby_messages.h"
#include "protocol.h"

class Sender: public Thread {
private:
    uint16_t session_id;
    ServerProtocol protocol;
    bool closed = false;
    Queue<Snapshot>& out_queue;
    Queue<LobbyMessage>& lobby_queue;
    std::atomic<bool>& is_playing;
public:
    explicit Sender(Socket& skt, const uint16_t &id, Queue<Snapshot>&, Queue<LobbyMessage>&, std::atomic<bool>&);
    ~Sender();
    void run() override;
    void stop() override;
    void send(const Snapshot &snapshot);
};

#endif  // SERVER_SENDER_H
