#include "pewpewlaser.h"
#include "defminvalue.h"
#include "projectile/projectilegun.h"

#define VELOCITY 10
#define MAX_AMMO 12
#define MAX_DISTANCE 38
#define MIN_DISTANCE 35

#define GUN_WIDTH 20
#define GUN_HEIGHT 10

#define DUCK_WITH_GUN_Y_DIRECTION 13
#define DUCK_WITH_GUN_RIGHT_DIRECTION 10
#define DUCK_WITH_GUN_LEFT_DIRECTION 0

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

PewPewLaser::PewPewLaser(const uint16_t &pos_x, const uint16_t &pos_y) : Gun(GunType::PewPewLaser, Position(pos_x, pos_y), Size(GUN_WIDTH, GUN_HEIGHT)), GunAmmo(MAX_AMMO)
{
}

std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> PewPewLaser::shoot(bool &looking_right, bool &looking_up, const Position &duck_position)
{
    if (!have_ammo())
        return std::nullopt;
    std::pair<int, int> direction = get_direction(looking_right, looking_up);
    reduce_ammo();
    std::vector<std::shared_ptr<Projectile>> projectiles;
    uint16_t adjusted_pos_x = duck_position.x + (direction.first == 1 ? MIN_VALUE_RIGHT_DIRECTION_POS_X : MIN_VALUE_LEFT_DIRECTION_POS_X);
    Position projectile_position(adjusted_pos_x, duck_position.y);

    std::vector<std::shared_ptr<Dispersion>> dispersions = {
        nullptr,
        std::make_shared<DispersionHigh>(true),
        std::make_shared<DispersionHigh>()};

    for (auto &dispersion : dispersions)
        projectiles.push_back(std::make_shared<ProjectileGun>(ProjectileType::CowboyBullet, projectile_position, direction, VELOCITY, MAX_DISTANCE, dispersion));

    return std::make_optional(std::make_pair(projectiles, duck_position));
}

Position PewPewLaser::get_position_in_duck(const uint16_t &height_duck, const Position &duck, const bool &looking_right)
{
    (void)height_duck;
    (void)looking_right;
    uint16_t pos_x = duck.x + (looking_right ? DUCK_WITH_GUN_RIGHT_DIRECTION : DUCK_WITH_GUN_LEFT_DIRECTION);
    uint16_t pos_y = duck.y + DUCK_WITH_GUN_Y_DIRECTION;
    return Position(pos_x, pos_y);
}

PewPewLaser::~PewPewLaser()
{
}
