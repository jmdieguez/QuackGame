#ifndef SERVER_SENDER_H
#define SERVER_SENDER_H



#include <memory>
#include "../common/queue.h"
#include "../common/socket.h"
#include "../common/thread.h"
#include "client_command.h"
#include "protocol.h"
#include "games_manager.h"
#include "../common/snapshots.h"
#include "receiver.h"

class Sender : public Thread {
private:
    uint16_t session_id;
    ServerProtocol protocol;
    bool closed = false;
    Queue<Snapshot> out_queue;
    Queue<ClientCommand>* receiver_queue;
    GamesManager& manager;
    std::atomic<bool> is_playing;
    Receiver receiver;
public:
    explicit Sender(Socket& skt, const uint16_t &id, GamesManager&);
    ~Sender();
    void run() override;
    void stop() override;
    void send(const Snapshot &snapshot);
    void start_receiver();
};

#endif  // SERVER_SENDER_H
