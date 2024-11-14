#ifndef SERVER_GAME_H
#define SERVER_GAME_H

#include <memory>
#include <map>

#include "../client_command.h"
#include "../../common/snapshots.h"
#include "../../common/soundtype.h"
#include "gun/gun.h"
#include "gun/cowboypistol.h"
#include "gun/explosion.h"
#include "map.h"
#include "duck.h"

class Game
{
private:
    int current_players = 0;
    int required_players = 2;
    Map map;
    std::map<uint8_t, Duck> ducks;
    std::vector<Position> spawns;
    std::vector<std::shared_ptr<Projectile>> projectiles;
    std::vector<SoundType> sounds;
    std::vector<Explosion> explosions;

    void verify_hit_ducks();
    void move_grenade(std::shared_ptr<Projectile> &p);
    void moves_projectiles(Map &map);
    void remove_projectiles();

public:
    Game(const std::string &map_file);
    void process(ClientCommand &command);
    void step();
    bool started = false;
    void add_player(const uint16_t &id);
    Snapshot get_status();
    ~Game() {}
};

#endif // SERVER_GAME_H