#ifndef MAGNUM_H
#define MAGNUM_H

#include "dispersion.h"
#include "moveback.h"
#include "gun.h"

class Magnum : public Gun, protected Dispersion, protected MoveBack
{
private:
    uint8_t ammo;

public:
    explicit Magnum(uint16_t pos_x, uint16_t pos_y);
    std::pair<Projectile, Position> shoot(bool &looking_right, bool &looking_up, const Position &duck_position) override;
    GunNoEquippedSnapshot get_status() override;
    bool have_ammo() override;
    GunType get_type() override;
    ~Magnum();
};

#endif // MAGNUM_H