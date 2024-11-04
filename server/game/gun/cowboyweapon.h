#ifndef COWBOY_WEAPON_H
#define COWBOY_WEAPON_H

#include "gun.h"

class CowboyWeapon : public Gun
{
private:
    uint16_t pos_x;
    uint16_t pos_y;

public:
    explicit CowboyWeapon(uint16_t pos_x, uint16_t pos_y);
    ShootEvent shoot(bool &looking_right, bool &looking_up) override;
    GunNoEquippedSnapshot get_status() override;
    ~CowboyWeapon();
};

#endif // COWBOY_WEAPON_H