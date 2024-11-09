#include "grenade.h"
#include "projectile/projectilegrenade.h"

#define MAX_AMMO 1
#define MAX_DISTANCE 10
#define VELOCITY 5
#define TIME_EXPLOSION 100

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Grenade::Grenade(uint16_t pos_x, uint16_t pos_y) : Gun(GunType::Grenade, pos_x, pos_y), GunAmmo(MAX_AMMO), start_explosion_state(false), time_explosion(TIME_EXPLOSION) {}

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

std::shared_ptr<Projectile> Grenade::get_projectile(bool &looking_right, bool &looking_up)
{
    (void)looking_up;
    if (!start_explosion_state)
        return nullptr;
    Position position(pos_x, pos_y);
    std::pair<int, int> directions;
    if (looking_right)
        directions = {1, -1};
    if (!looking_right)
        directions = {-1, -1};
    return std::make_shared<ProjectileGrenade>(ProjectileType::Grenade, position, directions, VELOCITY);
}

Grenade::~Grenade()
{
}
