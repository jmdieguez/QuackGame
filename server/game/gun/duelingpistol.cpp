#include "duelingpistol.h"
#include "defminvalue.h"

#define VELOCITY 10
#define MAX_AMMO 1
#define MAX_DISTANCE 5

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

DuelingPistol::DuelingPistol(uint16_t pos_x, uint16_t pos_y) : Gun(GunType::DuelingPistol, pos_x, pos_y), GunAmmo(MAX_AMMO)
{
}

std::optional<std::pair<Projectile, Position>> DuelingPistol::shoot(bool &looking_right, bool &looking_up, const Position &duck_position)
{
    if (!have_ammo())
        return std::nullopt;
    std::pair<int, int> directions = getDirections(looking_right, looking_up);
    uint16_t adjusted_pos_x = duck_position.pos_x + (directions.first == 1 ? MIN_VALUE_RIGHT_DIRECTION_POS_X : MIN_VALUE_LEFT_DIRECTION_POS_X);
    Position projectile_position(adjusted_pos_x, duck_position.pos_y);
    Projectile projectile(ProjectileType::CowboyBullet, projectile_position, directions, MAX_DISTANCE, VELOCITY);
    std::pair<Projectile, Position> result(projectile, duck_position);
    reduce_ammo();
    return std::optional<std::pair<Projectile, Position>>(result);
}

DuelingPistol::~DuelingPistol()
{
}
