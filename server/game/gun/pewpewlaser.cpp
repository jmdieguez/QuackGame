#include "pewpewlaser.h"
#include "defminvalue.h"
#include "projectile/projectilegun.h"

#define VELOCITY 10
#define MAX_AMMO 12
#define MAX_DISTANCE 38
#define MIN_DISTANCE 35

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

PewPewLaser::PewPewLaser(uint16_t pos_x, uint16_t pos_y) : Gun(GunType::PewPewLaser, pos_x, pos_y), GunAmmo(MAX_AMMO)
{
}

std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> PewPewLaser::shoot(bool &looking_right, bool &looking_up, const Position &duck_position)
{
    if (!have_ammo())
        return std::nullopt;
    std::pair<int, int> directions = get_directions(looking_right, looking_up);
    auto directions_shotgun = apply_dispersion_pew_pew_laser(directions);
    reduce_ammo();
    std::vector<std::shared_ptr<Projectile>> projectiles;
    for (auto dir : directions_shotgun)
    {
        uint16_t adjusted_pos_x = duck_position.pos_x + (dir.first == 1 ? MIN_VALUE_RIGHT_DIRECTION_POS_X : MIN_VALUE_LEFT_DIRECTION_POS_X);
        Position projectile_position(adjusted_pos_x, duck_position.pos_y);
        uint8_t distance = (dir.first == 1 && dir.second == 0) || (dir.first == -1 && dir.second == 0) ? MAX_DISTANCE : MIN_DISTANCE;
        projectiles.push_back(std::make_shared<ProjectileGun>(ProjectileType::CowboyBullet, projectile_position, dir, VELOCITY, distance));
    }
    std::pair<std::vector<std::shared_ptr<Projectile>>, Position> result(projectiles, duck_position);
    return std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>>(result);
}

PewPewLaser::~PewPewLaser()
{
}
