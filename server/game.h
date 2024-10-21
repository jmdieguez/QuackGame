#ifndef SERVER_GAME_H
#define SERVER_GAME_H

#include "../common/game_dto.h"
#include "map.h"

class Game {
private:
    Map map;
public:
    Game();
    ~Game() {}

    GameDTO get_status();
};

#endif // SERVER_GAME_H
