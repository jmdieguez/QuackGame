#include "cowboypistol.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

CowboyPistol::CowboyPistol(uint16_t pos_x, uint16_t pos_y)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}

ShootEvent CowboyPistol::shoot(bool &looking_right, bool &looking_up)
{
    (void)looking_right;
    (void)looking_up;
    return ShootEvent();
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