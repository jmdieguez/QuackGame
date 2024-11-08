#include "cowboypistol.h"
#include "defminvalue.h"

#define VELOCITY 10
#define MAX_AMMO 6
#define MAX_DISTANCE 20

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

CowboyPistol::CowboyPistol(uint16_t pos_x, uint16_t pos_y) : ammo(MAX_AMMO)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}

bool CowboyPistol::have_ammo()
{
    return ammo > 0;
}

std::pair<Projectile, Position> CowboyPistol::shoot(bool &looking_right, bool &looking_up, const Position &duck_position)
{
    std::pair<int, int> directions = getDirections(looking_right, looking_up);
    ammo--;
    uint16_t adjusted_pos_x = duck_position.pos_x + (directions.first == 1 ? MIN_VALUE_RIGHT_DIRECTION_POS_X : MIN_VALUE_LEFT_DIRECTION_POS_X);
    Position projectile_position(adjusted_pos_x, duck_position.pos_y);
    Projectile projectile(ProjectileType::CowboyBullet, projectile_position, directions, MAX_DISTANCE, VELOCITY);
    std::pair<Projectile, Position> result(projectile, duck_position);
    return result;
}

GunNoEquippedSnapshot CowboyPistol::get_status()
{
    return GunNoEquippedSnapshot(GunType::CowboyPistol, pos_x, pos_y);
}

GunType CowboyPistol::get_type()
{
    return GunType::CowboyPistol;
}

CowboyPistol::~CowboyPistol()
{
}