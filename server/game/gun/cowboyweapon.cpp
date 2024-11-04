#include "cowboyweapon.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

CowboyWeapon::CowboyWeapon(uint16_t pos_x, uint16_t pos_y) : pos_x(pos_x), pos_y(pos_y)
{
}

ShootEvent CowboyWeapon::shoot(bool &looking_right, bool &looking_up)
{
    (void)looking_right;
    (void)looking_up;
    return ShootEvent();
}

GunNoEquippedSnapshot CowboyWeapon::get_status()
{
    return GunNoEquippedSnapshot(GunType::CowboyPistol, pos_x, pos_y);
}

CowboyWeapon::~CowboyWeapon()
{
}