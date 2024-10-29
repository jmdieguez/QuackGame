#ifndef SERVER_SESSION_H
#define SERVER_SESSION_H

#include <memory>

#include "../common/snapshots.h"
#include "client_command.h"
#include "../common/socket.h"
#include "receiver.h"
#include "sender.h"

class Session
{
private:
    uint16_t id;
    bool finished = false;
    Socket socket;
    Sender sender;
    Receiver receiver;

    void check_close_socket();

public:
    Session(Socket &&client, std::shared_ptr<Queue<ClientCommand>> &recv_q, uint16_t &s_id);
    ~Session();
    void run();
    void stop();
    void send(const Snapshot &msg);
    bool has_finished() const;
};

#endif // SERVER_SESSION_H
