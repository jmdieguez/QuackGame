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
    void createRoom(const std::string&);
    void joinRoom(const uint16_t&);
};

#endif // LOBBY_H
