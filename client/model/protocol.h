#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "../../common/snapshots.h"
#include "../../common/socket.h"
#include "../../common/client_actions.h"

class ClientProtocol
{
private:
     Socket &skt;

public:
    //ClientProtocol();
    explicit ClientProtocol(Socket&);
    void read_snapshot(Snapshot&, bool&);
    void send_action(const ClientActionType&, bool&);
    //  bool readDuck(Duck &);
};

#endif // PROTOCOL_H
