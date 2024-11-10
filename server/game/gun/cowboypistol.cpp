#include "cowboypistol.h"
#include "defminvalue.h"
#include "projectile/projectilegun.h"

#define VELOCITY 10
#define MAX_AMMO 6
#define MAX_DISTANCE 20

#define GUN_WIDTH 20
#define GUN_HEIGHT 10

#define DUCK_WITH_GUN_Y_DIRECTION 13
#define DUCK_WITH_GUN_RIGHT_DIRECTION 10
#define DUCK_WITH_GUN_LEFT_DIRECTION 0

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

CowboyPistol::CowboyPistol(const uint16_t &pos_x, const uint16_t &pos_y) : Gun(GunType::CowboyPistol, Position(pos_x, pos_y), Size(GUN_WIDTH, GUN_HEIGHT)), GunAmmo(MAX_AMMO)
{
}

std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> CowboyPistol::shoot(bool &looking_right, bool &looking_up, const Position &duck_position)
{
    if (!have_ammo())
        return std::nullopt;
    std::pair<int, int> directions = get_direction(looking_right, looking_up);
    reduce_ammo();
    uint16_t adjusted_pos_x = duck_position.x + (directions.first == 1 ? MIN_VALUE_RIGHT_DIRECTION_POS_X : MIN_VALUE_LEFT_DIRECTION_POS_X);
    Position projectile_position(adjusted_pos_x, duck_position.y);
    std::vector<std::shared_ptr<Projectile>> projectiles;
    ProjectileType type = ProjectileType::CowboyBullet;
    projectiles.push_back(std::make_shared<ProjectileGun>(type, projectile_position, directions, VELOCITY, MAX_DISTANCE));
    std::pair<std::vector<std::shared_ptr<Projectile>>, Position> result(projectiles, duck_position);
    return std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>>(result);
}
Position CowboyPistol::get_position_in_duck(const uint16_t &height_duck, const Position &duck, const bool &looking_right)
{
    (void)height_duck;
    (void)looking_right;
    uint16_t pos_x = duck.x + (looking_right ? DUCK_WITH_GUN_RIGHT_DIRECTION : DUCK_WITH_GUN_LEFT_DIRECTION);
    uint16_t pos_y = duck.y + DUCK_WITH_GUN_Y_DIRECTION;
    return Position(pos_x, pos_y);
}
CowboyPistol::~CowboyPistol()
{
}