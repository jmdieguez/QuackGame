#include "duelingpistol.h"
#include "defminvalue.h"
#include "projectile/projectilegun.h"

#define VELOCITY 10
#define MAX_AMMO 1
#define MAX_DISTANCE 5
#define WIDTH 26
#define HEIGHT 16

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

DuelingPistol::DuelingPistol(const uint16_t &pos_x, const uint16_t &pos_y) : Gun(GunType::DuelingPistol, Position(pos_x, pos_y), Size(WIDTH, HEIGHT)), GunAmmo(MAX_AMMO)
{
}

std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> DuelingPistol::shoot(bool &looking_right, bool &looking_up, const Position &duck_position)
{
    if (!have_ammo())
        return std::nullopt;
    std::pair<int, int> directions = get_directions(looking_right, looking_up);
    reduce_ammo();
    uint16_t adjusted_pos_x = duck_position.x + (directions.first == 1 ? MIN_VALUE_RIGHT_DIRECTION_POS_X : MIN_VALUE_LEFT_DIRECTION_POS_X);
    Position projectile_position(adjusted_pos_x, duck_position.y);
    std::vector<std::shared_ptr<Projectile>> projectiles;
    ProjectileType type = ProjectileType::CowboyBullet;
    projectiles.push_back(std::make_shared<ProjectileGun>(type, projectile_position, directions, VELOCITY, MAX_DISTANCE));
    std::pair<std::vector<std::shared_ptr<Projectile>>, Position> result(projectiles, duck_position);
    return std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>>(result);
}

DuelingPistol::~DuelingPistol()
{
}
