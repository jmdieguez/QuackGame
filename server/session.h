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
public:
    const uint16_t id;
    Session(Socket &client, std::shared_ptr<Queue<ClientCommand>> &recv_q, const uint16_t &s_id);
    ~Session();
    void run();
    void stop();
    void send(const Snapshot &msg);
    bool has_finished() const;
private:
    bool finished = false;
    Socket socket;
    Sender sender;
    Receiver receiver;

    void check_close_socket();
};

#endif // SERVER_SESSION_H