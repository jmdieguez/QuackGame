#ifndef SERVER_SESSION_H
#define SERVER_SESSION_H

#include <memory>

#include "client_command.h"
#include "../common/socket.h"
#include "receiver.h"
#include "sender.h"

class Session {
private:
    bool finished = false;
    Socket socket;
    Sender sender;
    Receiver receiver;

public:
    Session(Socket&& client, std::shared_ptr<Queue<ClientCommand>>& recv_q);
    ~Session();
    void run();
    void stop();
    // void send(const ServerMessage& msg);
    bool has_finished() const;
};

#endif  // SERVER_SESSION_H
