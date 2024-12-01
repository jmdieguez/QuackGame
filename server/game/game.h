#ifndef SERVER_GAME_H
#define SERVER_GAME_H

#include <memory>
#include <map>

#include "duck/duck.h"
#include "../client_command.h"
#include "../../common/snapshots.h"
#include "../../common/color.h"
#include "gun/gun.h"
#include "gun/cowboypistol.h"
#include "gun/explosion.h"
#include "map.h"
#include "gun_spawn.h"
#include "camera.h"
#include "manager/projectilemanager.h"
#include "manager/explosionmanager.h"

enum class RandomSelection
{
    SpawnGun = 0,
    Explode,
    Nothing
};

class Game
{
private:
    unsigned required_players = 2;
    unsigned current_map = 0;
    unsigned round = 0;
    bool initialize = true;
    std::vector<Map> maps;
    std::vector<uint8_t> player_ids;
    std::map<uint16_t, Duck> ducks;
    ExplosionManager explosions;
    ProjectileManager projectiles;
    std::map<uint8_t, uint8_t> victories;
    std::map<uint16_t, Color> colors;
    std::map<Position, Box> boxes;
    std::map<Position, GunSpawn> gun_spawns;
    std::map<Position, ArmorType> armor;
    uint16_t gun_id = 0;
    std::map<uint8_t, std::shared_ptr<Gun>> guns;
    // Random number generator
    std::random_device rd;
    std::mt19937 rng;
    std::uniform_int_distribution<int> dist;
    // Gun type to lambda mapping. This calls spawn_gun
    std::vector<std::function<void(const Position &)>> gun_spawners;
    Camera camera;
    uint8_t winner_id = 0;

    bool verify_hit_duck(Duck &duck, std::shared_ptr<Projectile> &projectile);
    void spawn_players();
    void check_intersect(Hitbox explosion_hitbox);
    int calculate_winner(const std::vector<uint8_t> &possible_winners);
    void check_for_winner(const std::map<uint8_t, Duck &> &ducks_alive);
    void spawn_in_boxes(const Position &position_box, const Position &position_as_pixels);

    std::vector<GunNoEquippedSnapshot> get_guns_snapshots();
    template <typename T>
    void spawn_gun(const Position &position_gun);
    void spawn_random_gun(const Position &position);
    void move_guns();
    void remove_gun(const uint16_t &id);
    void spawn_guns();
    void update_camera(std::map<uint8_t, Duck &> &ducks);

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
