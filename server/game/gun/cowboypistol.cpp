#include "cowboypistol.h"
#include "defminvalue.h"

#define VELOCITY 10
#define MAX_AMMO 6
#define MAX_DISTANCE 20

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

CowboyPistol::CowboyPistol(uint16_t pos_x, uint16_t pos_y) : Gun(GunType::CowboyPistol, pos_x, pos_y), GunAmmo(MAX_AMMO)
{
}
std::optional<std::pair<std::vector<Projectile>, Position>> CowboyPistol::shoot(bool &looking_right, bool &looking_up, const Position &duck_position)
{
    if (!have_ammo())
        return std::nullopt;
    std::pair<int, int> directions = getDirections(looking_right, looking_up);
    reduce_ammo();
    uint16_t adjusted_pos_x = duck_position.pos_x + (directions.first == 1 ? MIN_VALUE_RIGHT_DIRECTION_POS_X : MIN_VALUE_LEFT_DIRECTION_POS_X);
    Position projectile_position(adjusted_pos_x, duck_position.pos_y);
    Projectile projectile(ProjectileType::CowboyBullet, projectile_position, directions, MAX_DISTANCE, VELOCITY);
    std::vector<Projectile> projectiles;
    projectiles.push_back(projectile);
    std::pair<std::vector<Projectile>, Position> result(projectiles, duck_position);
    return std::optional<std::pair<std::vector<Projectile>, Position>>(result);
}
CowboyPistol::~CowboyPistol()
{
}