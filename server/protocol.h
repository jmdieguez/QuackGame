#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include "../common/snapshots.h"
#include "../common/client_actions.h"
#include "../common/socket.h"

class ServerProtocol {
private:
  Socket& skt;
public:
    explicit ServerProtocol(Socket&);
    ActionMessage read_actions(bool& closed);
    void send_snapshot(const Snapshot& snapshot, bool& was_closed);
};

#endif  // SERVER_PROTOCOL_H
