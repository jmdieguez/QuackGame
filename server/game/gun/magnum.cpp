#include "magnum.h"

#include <random>

#include "defminvalue.h"

#define VELOCITY 10
#define MAX_AMMO 6
#define MAX_DISTANCE 20
#define DISPERSION_VALUE 1
#define BACK 5

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Magnum::Magnum(uint16_t pos_x, uint16_t pos_y) : Gun(GunType::Magnum, pos_x, pos_y), GunAmmo(MAX_AMMO)
{
}

std::optional<std::pair<std::vector<Projectile>, Position>> Magnum::shoot(bool &looking_right, bool &looking_up, const Position &duck_position)
{
    if (!have_ammo())
        return std::nullopt;
    std::pair<int, int> directions = get_directions(looking_right, looking_up);
    reduce_ammo();
    apply_dispersion(directions, DISPERSION_VALUE);
    uint16_t adjusted_pos_x = duck_position.pos_x + (directions.first == 1 ? MIN_VALUE_RIGHT_DIRECTION_POS_X : MIN_VALUE_LEFT_DIRECTION_POS_X);
    Position projectile_position(adjusted_pos_x, duck_position.pos_y);
    Projectile projectile(ProjectileType::CowboyBullet, projectile_position, directions, MAX_DISTANCE, VELOCITY);
    std::vector<Projectile> projectiles;
    projectiles.push_back(projectile);
    Position new_position = move_back(duck_position, looking_right, BACK);
    std::pair<std::vector<Projectile>, Position> result(projectiles, new_position);
    return std::optional<std::pair<std::vector<Projectile>, Position>>(result);
}

Magnum::~Magnum()
{
}