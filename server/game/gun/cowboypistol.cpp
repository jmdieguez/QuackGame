#include "cowboypistol.h"

#define VELOCITY 3
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
    Projectile projectile(ProjectileType::CowboyBullet, duck_position, directions, MAX_DISTANCE, VELOCITY);
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