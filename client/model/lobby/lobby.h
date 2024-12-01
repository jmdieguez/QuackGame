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

public:
    explicit Lobby(ClientProtocol &);
    ~Lobby();
    std::vector<UserLobbyInfo> create_room(const std::string &);
    std::vector<UserLobbyInfo> get_users();
    void join_room(const uint16_t &);
    void start_game(bool &);
    void get_game_list(std::map<uint16_t, std::string> &games);
};

#endif // LOBBY_H
