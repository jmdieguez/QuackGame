#include "grenade.h"
#include "projectile/projectilegrenade.h"

#define MAX_AMMO 1
#define MAX_DISTANCE 10
#define VELOCITY 5
#define TIME_EXPLOSION 100

#define GUN_WIDTH 15
#define GUN_HEIGHT 15

#define DUCK_WITH_GUN_Y_DIRECTION 13
#define DUCK_WITH_GUN_RIGHT_DIRECTION 0
#define DUCK_WITH_GUN_LEFT_DIRECTION 17

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Grenade::Grenade(const uint16_t &pos_x, const uint16_t &pos_y) : Gun(GunType::Grenade, Position(pos_x, pos_y), Size(GUN_WIDTH, GUN_HEIGHT)), GunAmmo(MAX_AMMO), start_explosion_state(false), time_explosion(TIME_EXPLOSION) {}

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

Position Grenade::get_position_in_duck(const uint16_t &height_duck, const Position &duck, const bool &looking_right)
{
    (void)height_duck;
    (void)looking_right;
    uint16_t pos_x = duck.x + (looking_right ? DUCK_WITH_GUN_RIGHT_DIRECTION : DUCK_WITH_GUN_LEFT_DIRECTION);
    uint16_t pos_y = duck.y + DUCK_WITH_GUN_Y_DIRECTION;
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
