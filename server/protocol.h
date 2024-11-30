#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include "../common/snapshots.h"
#include "../common/client_actions.h"
#include "../common/lobby_messages.h"
#include "../common/socket.h"
#include "../common/queue.h"
#include <vector>

class ServerProtocol
{
private:
    Socket &skt;
    void send_data(const uint16_t &data);
    void send_data_float(const float &data);
    void send_duck_status(const DuckStatus &status);
    void send_duck(const DuckSnapshot &duck);
    void send_gun(const GunNoEquippedSnapshot &gun);
    void send_explosion(const ExplosionSnapshot &explosion);
    void send_map_component(const MapComponent &component);
    void send_projectile(const ProjectileSnapshot &projectile);
    void send_box(const BoxSnapshot &box);
    void send_name(const std::vector<unsigned char> &);
    void read_name(std::string &name);
    void send_duck_color(Color color);

public:
    explicit ServerProtocol(Socket &);
    ActionMessage read_action();
    ActionLobby read_lobby();
    void send_snapshot(const Snapshot &snapshot);
    void send_lobby_info(const std::vector<LobbyMessage> &lobby_info);
    void send_not_ready();
    void send_ready();
};

#endif // SERVER_PROTOCOL_H
