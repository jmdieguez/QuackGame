#include "grenade.h"
#include "projectile/projectilegrenade.h"

#define MAX_AMMO 1
#define MAX_DISTANCE 10
#define VELOCITY 5
#define TIME_EXPLOSION 100

#define GUN_WIDTH 15
#define GUN_HEIGHT 15

#define HORIZONTAL_Y 13
#define HORIZONTAL_RIGHT 0
#define HORIZONTAL_LEFT 17

#define VERTICAL_RIGHT 0
#define VERTICAL_LEFT 8

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Grenade::Grenade(const uint16_t &pos_x, const uint16_t &pos_y) : Gun(GunType::Grenade, Position(pos_x, pos_y), Size(GUN_WIDTH, GUN_HEIGHT)), GunAmmo(MAX_AMMO),
                                                                 position_gun(HORIZONTAL_Y, HORIZONTAL_RIGHT, HORIZONTAL_LEFT, VERTICAL_RIGHT, VERTICAL_LEFT),
                                                                 start_explosion_state(false), time_explosion(TIME_EXPLOSION) {}

std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> Grenade::shoot(bool &looking_right, bool &looking_up, const Position &duck_position)
{
    (void)looking_right;
    (void)looking_up;
    (void)duck_position;
    if (!have_ammo())
        return std::nullopt;
    reduce_ammo();
    start_explosion_state = true;
    return std::nullopt;
}

Position Grenade::get_position_in_duck(const uint16_t &height_duck, const Position &duck, const bool &looking_right, const bool &looking_up)
{
    (void)height_duck;
    (void)looking_up;
    uint16_t pos_x = duck.x + (looking_right ? HORIZONTAL_RIGHT : HORIZONTAL_LEFT);
    uint16_t pos_y = duck.y + HORIZONTAL_Y;
    return Position(pos_x, pos_y);
}

std::shared_ptr<Projectile> Grenade::get_projectile(bool &looking_right, bool &looking_up)
{
    (void)looking_up;
    if (!start_explosion_state)
        return nullptr;
    std::pair<int, int> directions;
    if (looking_right)
        directions = {1, -1};
    if (!looking_right)
        directions = {-1, -1};
    ProjectileType type = ProjectileType::Grenade;
    return std::make_shared<ProjectileGrenade>(type, position, directions, VELOCITY);
}

Grenade::~Grenade()
{
}