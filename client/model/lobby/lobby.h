#ifndef LOBBY_H
#define LOBBY_H

#include "../protocol.h"
#include <string>
#include <cstdint>

class Lobby {
private:
  ClientProtocol &protocol;
public:
    explicit Lobby(ClientProtocol&);
    ~Lobby();
    void create_room(const std::string&);
    void join_room(const uint16_t&);
    void start_game();
    void get_game_list(std::map<uint16_t, std::string>& games);
};

#endif // LOBBY_H
