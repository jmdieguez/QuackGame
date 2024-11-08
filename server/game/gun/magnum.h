#ifndef MAGNUM_H
#define MAGNUM_H

#include "dispersion.h"
#include "moveback.h"
#include "gunammo.h"
#include "gun.h"

class Magnum : public Gun, public GunAmmo, protected Dispersion, protected MoveBack
{
private:
public:
    explicit Magnum(uint16_t pos_x, uint16_t pos_y);
    std::optional<std::pair<Projectile, Position>> shoot(bool &looking_right, bool &looking_up, const Position &duck_position) override;
    ~Magnum();
};

#endif // MAGNUM_H