#ifndef USER_LOBBY_INFO_H
#define USER_LOBBY_INFO_H

#include <cstdint>

class UserLobbyInfo
{
private:
    uint16_t id;
    std::string color;

public:
    UserLobbyInfo() {};
    UserLobbyInfo(uint16_t id, std::string color) : id(id), color(color) {};
    uint16_t get_id()
    {
        return id;
    }

    std::string get_color()
    {
        return color;
    }

    ~UserLobbyInfo() {};
};

#endif // USER_LOBBY_INFO_H