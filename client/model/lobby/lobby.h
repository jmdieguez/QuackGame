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
    bool start_game();
};

#endif // LOBBY_H
