#ifndef COWBOY_PISTOL_H
#define COWBOY_PISTOL_H

#include "gun.h"

class CowboyPistol : public Gun
{
private:
public:
    explicit CowboyPistol(uint16_t pos_x, uint16_t pos_y);
    Projectile shoot(bool &looking_right, bool &looking_up, Position &duck_position) override;
    GunNoEquippedSnapshot get_status() override;
    GunType get_type() override;
    ~CowboyPistol();
};

#endif // COWBOY_PISTOL_H