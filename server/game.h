#ifndef SERVER_GAME_H
#define SERVER_GAME_H

#include <map>
#include <memory>
#include <string>

#include "common_box_id.h"
#include "server_item.h"
#include "server_reward.h"

class Game {
private:
    std::map<BoxID, std::unique_ptr<Item>> boxes;

public:
    Game();
    ~Game();

    int step();
    Reward pickup(const BoxID& box_id);
};

#endif  // SERVER_GAME_H
