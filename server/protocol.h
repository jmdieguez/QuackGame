#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include "../common/snapshots.h"
#include "../common/client_actions.h"
#include "../common/socket.h"

class ServerProtocol
{
private:
    Socket &skt;
    void send_data(const uint16_t &data);
    void send_duck_status(const DuckStatus &status);
    void send_duck(const DuckSnapshot &duck);
    void send_gun(const GunNoEquippedSnapshot &gun);
    void send_map_component(const MapComponent &component);
    void send_projectile(const ProjectileSnapshot &projectile);

public:
    explicit ServerProtocol(Socket &);
    ActionMessage read_action();
    void send_snapshot(const Snapshot &snapshot);
};

#endif // SERVER_PROTOCOL_H
