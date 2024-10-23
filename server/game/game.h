#ifndef SERVER_GAME_H
#define SERVER_GAME_H

#include <vector>

#include "../../common/snapshots.h"
#include "map.h"
#include "duck.h"

class Game {
private:
    Map map;
    std::vector<Duck> ducks;
public:
    Game();
    ~Game() {}

    void step();
    Snapshot get_status();
};

#endif // SERVER_GAME_H
