#ifndef SERVER_GAME_H
#define SERVER_GAME_H

#include <memory>
#include <map>

#include "duck/duck.h"
#include "../client_command.h"
#include "../../common/snapshots.h"
#include "../../common/soundtype.h"
#include "gun/gun.h"
#include "gun/cowboypistol.h"
#include "gun/explosion.h"
#include "map.h"

class Game
{
private:
    unsigned required_players = 2;
    unsigned current_map = 0;
    unsigned round = 0;
    bool initialize = true;
    std::vector<Map> maps;
    std::vector<uint8_t> player_ids;
    std::map<uint8_t, Duck> ducks;
    std::vector<std::shared_ptr<Projectile>> projectiles;
    std::vector<SoundType> sounds;
    std::vector<Explosion> explosions;
    std::map<uint8_t, uint8_t> victories;
    void verify_hit_ducks();
    void move_grenade(std::shared_ptr<Projectile> &p);
    void move_projectiles();
    void remove_projectiles();
    void spawn_players();
    int calculate_winner(std::vector<uint8_t> possible_winners);
    void check_for_winner(const std::vector<uint8_t> &ducks_alive);

public:
    Game();
    void process(ClientCommand &command);
    void step();
    bool started = false;
    bool ended = false;
    void add_player(const uint16_t &id);
    Snapshot get_status();
    ~Game() {}
};

#endif // SERVER_GAME_H