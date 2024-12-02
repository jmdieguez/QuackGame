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
    uint16_t game_mode;
public:
    explicit Lobby(ClientProtocol &);
    ~Lobby();
    void create_room(const std::string&);
    std::vector<UserLobbyInfo> join_room(const uint16_t &);
    std::vector<UserLobbyInfo> get_users();
    std::vector<UserLobbyInfo> send_create_game();
    void prepare_multiplayer_game();
    void prepare_single_player_game();
    void start_game(bool &);
    void get_game_list(std::map<uint16_t, std::string> &games);
};

#endif // LOBBY_H
