#ifndef LOBBY_H
#define LOBBY_H

#include "../protocol.h"
#include <string>
#include <cstdint>
#include <atomic>

class Lobby
{
private:
    ClientProtocol &protocol;
    std::vector<UserLobbyInfo> users;
    std::string room_name;
    uint16_t game_mode = 0;
    uint16_t game_id = 0;
public:
    explicit Lobby(ClientProtocol &);
    ~Lobby();
    void create_room(const std::string&);
    void join_room();
    std::vector<UserLobbyInfo> get_users();
    std::vector<UserLobbyInfo> send_create_game();
    void prepare_multiplayer_game();
    void prepare_single_player_game();
    void start_game(bool &);
    void select_game(const uint16_t &);
    void get_game_list(std::map<uint16_t, std::string> &games);
};

#endif // LOBBY_H
