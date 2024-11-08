#include "cowboypistol.h"
#include "defminvalue.h"

#define VELOCITY 10
#define MAX_AMMO 6
#define MAX_DISTANCE 20

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

std::pair<int, int> CowboyPistol::getDirections(bool looking_right, bool looking_up)
{
    int direction_x = looking_right ? 1 : -1;
    int direction_y = looking_up ? 1 : 0;
    if (looking_up)
        direction_x = 0;
    return {direction_x, direction_y};
}

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

Projectile CowboyPistol::shoot(bool &looking_right, bool &looking_up, Position &duck_position)
{
    std::pair<int, int> directions = getDirections(looking_right, looking_up);
    ammo--;
    uint16_t adjusted_pos_x = duck_position.pos_x + (directions.first == 1 ? MIN_VALUE_RIGHT_DIRECTION_POS_X : MIN_VALUE_LEFT_DIRECTION_POS_X);
    Position projectile_position(adjusted_pos_x, duck_position.pos_y);
    Projectile projectile(ProjectileType::CowboyBullet, projectile_position, directions, MAX_DISTANCE, VELOCITY);
    return projectile;
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