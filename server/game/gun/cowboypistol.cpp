#include "cowboypistol.h"

#define VELOCITY 5

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

CowboyPistol::CowboyPistol(uint16_t pos_x, uint16_t pos_y)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}

Projectile CowboyPistol::shoot(bool &looking_right, bool &looking_up, Position &duck_position)
{
    int direction_x = looking_right ? 1 : -1;
    int direction_y = looking_up ? 1 : 0;
    if (looking_up)
        direction_x = 0;
    std::pair<int, int> directions(direction_x, direction_y);
    Projectile projectile(ProjectileType::CowboyBullet, duck_position, directions, 20, VELOCITY);
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