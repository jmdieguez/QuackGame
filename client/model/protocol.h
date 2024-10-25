#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "../../common/snapshots.h"
#include "../../common/socket.h"
#include "../../common/client_actions.h"

class ClientProtocol {
private:
    Socket &skt;
    void read_data(uint16_t& data);
public:
    //ClientProtocol();
    explicit ClientProtocol(Socket&);
    void read_snapshot(Snapshot&);
    void send_action(const ClientActionType&, bool&);
    //  bool readDuck(Duck &);
};

#endif // PROTOCOL_H
