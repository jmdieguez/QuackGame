#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include "../common/snapshots.h"
#include "../common/client_actions.h"
#include "../common/lobby_messages.h"
#include "../common/socket.h"
#include "../common/queue.h"
#include "../common/userlobbyinfo.h"
#include <vector>

class ServerProtocol
{
private:
    Socket &skt;
    void send_buffer(const std::vector<uint16_t>& buffer);
    void send_data_float(const float &data);
    void send_gun(const GunNoEquippedSnapshot &gun);
    void send_explosion(const ExplosionSnapshot &explosion);
    void send_map_component(const MapComponent &component);
    void send_projectile(const ProjectileSnapshot &projectile);
    void send_box(const BoxSnapshot &box);
    void send_name(const std::vector<unsigned char> &);
    void send_duck(const DuckSnapshot &duck);
    void read_data(uint16_t &data);
    void send_data(const uint16_t &data);

public:
    explicit ServerProtocol(Socket &);
    ActionMessage read_action();
    ActionLobby read_lobby();
    void send_snapshot(const Snapshot &snapshot);
    void send_users(std::vector<UserLobbyInfo> &users);
    void send_join_game_info(std::vector<UserLobbyInfo> &users);
    void send_lobby_info(const std::vector<LobbyMessage> &lobby_info);
    void send_not_ready();
    void send_ready();
    void read_name(std::string &name);
    void create_buffer_duck_positions(const DuckSnapshot &duck, std::vector<uint16_t> &buffer);
    void create_buffer_duck_status(const DuckStatus &status, std::vector<uint16_t> &buffer);
    void create_buffer_duck_color(const Color& color, std::vector<uint16_t>& buffer);
    void create_buffer_gun(const GunNoEquippedSnapshot& gun, std::vector<uint16_t>& buffer);
    void create_buffer_projectile(const ProjectileSnapshot& projectile, std::vector<uint16_t>& buffer);
    void create_buffer_explosion(const ExplosionSnapshot& explosion, std::vector<uint16_t>& buffer);
    void create_buffer_map_component(const MapComponent &component, std::vector<uint16_t> &buffer);
    void create_buffer_box(const BoxSnapshot &box, std::vector<uint16_t> &buffer);
};

#endif // SERVER_PROTOCOL_H
