#ifndef SERVER_GAME_H
#define SERVER_GAME_H

#include <memory>
#include <map>

#include "duck/duck.h"
#include "../client_command.h"
#include "../../common/snapshots.h"
#include "../../common/soundtype.h"
#include "../../common/color.h"
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
    std::map<uint16_t, Color> colors;
    std::map<Position, Box> boxes;
    
    bool verify_hit_box(Box &box, const Position &position, std::shared_ptr<Projectile> &projectile);
    bool verify_hit_duck(Duck &duck, std::shared_ptr<Projectile> &projectile);
    void verify_hits();
    void move_projectiles();
    void remove_projectiles();
    void decrement_explosions();
    void spawn_players();
    int calculate_winner(std::vector<uint8_t> possible_winners);
    void check_for_winner(const std::vector<uint8_t> &ducks_alive);

public:
    Game();
    void process(ClientCommand &command);
    void step();
    bool started = false;
    bool ended = false;
    void add_player(const uint16_t &id, Color color);
    Snapshot get_status();
    ~Game() {}
};

#endif // SERVER_GAME_H