#ifndef SERVER_RECEIVER_H
#define SERVER_RECEIVER_H

#include <memory>
#include "../common/queue.h"
#include "../common/socket.h"
#include "../common/thread.h"
#include "client_command.h"
#include "protocol.h"
#include "games_manager.h"
#include "../common/snapshots.h"

class Receiver : public Thread {
private:
    uint16_t session_id;
    Socket& client;                                    // Socket compartido con Sender
    Queue<Snapshot>& sender_queue;
    Queue<ClientCommand>* game_queue;
    ServerProtocol protocol;
    bool closed;
    std::atomic<bool>& is_playing;
public:
    Receiver(Socket& skt, const uint16_t &id, Queue<Snapshot>&, std::atomic<bool>&);
    ~Receiver();
    void run() override;
    void add_game_queue(Queue<ClientCommand>* queue);
};

#endif  // SERVER_RECEIVER_H
