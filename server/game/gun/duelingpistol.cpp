#include <cstdlib>
#include <ctime>

#include "duelingpistol.h"
#include "defminvalue.h"
#include "projectile/projectilegun.h"

#define VELOCITY 10
#define MAX_AMMO 1
#define MAX_DISTANCE 5

#define GUN_WIDTH 20
#define GUN_HEIGHT 10

#define HORIZONTAL_Y 13
#define HORIZONTAL_RIGHT 10
#define HORIZONTAL_LEFT 0

#define VERTICAL_RIGHT 0
#define VERTICAL_LEFT 12

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

bool DuelingPistol::random()
{
    std::srand(std::time(nullptr));
    return std::rand() % 2 == 0;
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

DuelingPistol::DuelingPistol(const uint16_t &pos_x, const uint16_t &pos_y) : Gun(GunType::DuelingPistol, Position(pos_x, pos_y), Size(GUN_WIDTH, GUN_HEIGHT)), GunAmmo(MAX_AMMO),
                                                                             position_gun(HORIZONTAL_Y, HORIZONTAL_RIGHT, HORIZONTAL_LEFT, VERTICAL_RIGHT, VERTICAL_LEFT)
{
}

std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> DuelingPistol::shoot(bool &looking_right, bool &looking_up, const Position &duck_position)
{
    if (!have_ammo())
        return std::nullopt;
    reduce_ammo();
    auto direction = get_direction(looking_right, looking_up);
    uint16_t adjusted_pos_x = duck_position.x + (direction.first == 1 ? MIN_VALUE_RIGHT_DIRECTION_POS_X : MIN_VALUE_LEFT_DIRECTION_POS_X);
    Position projectile_position(adjusted_pos_x, duck_position.y);
    std::shared_ptr<Dispersion> dispersion = std::make_shared<DispersionMedium>(random());
    std::vector<std::shared_ptr<Projectile>> projectiles = {
        std::make_shared<ProjectileGun>(ProjectileType::CowboyBullet, projectile_position, direction, VELOCITY, MAX_DISTANCE, dispersion)};
    return std::make_optional(std::make_pair(projectiles, duck_position));
}

Position DuelingPistol::get_position_in_duck(const uint16_t &height_duck, const Position &duck, const bool &looking_right, const bool &looking_up)
{
    return position_gun.get_position(height_duck, duck, looking_right, looking_up);
}

DuelingPistol::~DuelingPistol()
{
}