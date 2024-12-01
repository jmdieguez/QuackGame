#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "../../common/snapshots.h"
#include "../../common/socket.h"
#include "../../common/client_actions.h"
#include "../../common/lobby_messages.h"
#include "../../common/userlobbyinfo.h"
#include "../../common/clientidaction.h"
#include <memory>

class ClientProtocol
{
private:
    Socket &skt;
    DuckStatus read_status();
    ProjectileSnapshot read_projectile();
    ExplosionSnapshot read_explosion();
    void recv(void *data, size_t size);
    void send_name(const std::vector<unsigned char> &data);
    void read_data(uint16_t &data);
    void read_data_float(float &data);
    void read_string(std::string &string);

public:
    explicit ClientProtocol(Socket &);
    void read_snapshot(Snapshot &);
    std::vector<UserLobbyInfo> read_users_info();
    void send_action(const ClientActionType &, bool &);
    void send_id_action(const ClientIdAction &action, bool &was_closed);
    void get_game_list(uint16_t &game_id, std::string &name);
    void send_create_game(const uint16_t &num_player, const std::string &name);
    void send_join_game(const uint16_t &id, const uint16_t &num_player);
    void send_start_game();
    void read_start_game(ClientActionType &action);
    void read_list(std::map<uint16_t, std::string> &games);
    void send_game_list();
};

#endif // PROTOCOL_H
