#ifndef SERVER_GAME_H
#define SERVER_GAME_H

#include <memory>
#include <map>

#include "../client_command.h"
#include "../../common/snapshots.h"
#include "gun/gun.h"
#include "gun/cowboypistol.h"
#include "map.h"
#include "duck.h"

class Game
{
private:
    Map map;
    uint16_t gun_id;
    std::map<uint8_t, Duck> ducks;
    std::map<uint8_t, std::shared_ptr<Gun>> guns;

public:
    explicit Game(const std::string &map_file);
    ~Game() {}

    void process(ClientCommand &command);
    void step();
    Snapshot get_status();
};

#endif // SERVER_GAME_H