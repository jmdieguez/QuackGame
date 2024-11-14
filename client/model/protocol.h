#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "../../common/snapshots.h"
#include "../../common/socket.h"
#include "../../common/client_actions.h"

class ClientProtocol
{
private:
    Socket &skt;
    DuckStatus read_status();
    ProjectileSnapshot read_projectile();
    void read_data(uint16_t &data);
    void read_data_float(float &data);

public:
    explicit ClientProtocol(Socket &);
    void read_snapshot(Snapshot &);
    void send_action(const ClientActionType &, bool &);
};

#endif // PROTOCOL_H
