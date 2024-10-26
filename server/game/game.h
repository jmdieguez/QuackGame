#ifndef SERVER_GAME_H
#define SERVER_GAME_H

#include <map>

#include "../client_command.h"
#include "../../common/snapshots.h"
#include "map.h"
#include "duck.h"

class Game {
private:
    Map map;
    std::map<uint8_t, Duck> ducks;
public:
    Game();
    ~Game() {}

    void process(ClientCommand &command);
    void step();
    Snapshot get_status();
};

#endif // SERVER_GAME_H
