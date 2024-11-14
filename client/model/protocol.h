#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "../../common/snapshots.h"
#include "../../common/socket.h"
#include "../../common/client_actions.h"
#include "../../common/lobby_messages.h"
#include <memory>

class ClientProtocol
{
private:
    Socket &skt;
    DuckStatus read_status();
    ProjectileSnapshot read_projectile();
    void recv(void* data, size_t size);
    void send_name(const std::vector<unsigned char>& data);
public:
    void read_data(uint16_t &data);
    explicit ClientProtocol(Socket &);
    void read_snapshot(Snapshot &);
    void send_action(const ClientActionType &, bool &);
    void get_game_list(uint16_t& game_id, std::string& name);
    void send_create_game(const std::string&);
    void send_join_game(const uint16_t& id);
    void send_start_game();
    void read_list(std::map<uint16_t, std::string>& games);
    void send_game_list();
};

#endif // PROTOCOL_H
