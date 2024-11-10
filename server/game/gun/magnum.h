#ifndef MAGNUM_H
#define MAGNUM_H

#include "dispersion/dispersionlow.h"
#include "moveback.h"
#include "gunammo.h"
#include "gun.h"
#include "positiongun.h"

class Magnum : public Gun, public GunAmmo, protected MoveBack
{
private:
    PositionGun position_gun;
    bool random();

public:
    explicit Magnum(const uint16_t &pos_x, const uint16_t &pos_y);
    std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> shoot(bool &looking_right, bool &looking_up, const Position &duck_position) override;
    Position get_position_in_duck(const uint16_t &height_duck, const Position &duck, const bool &looking_right, const bool &looking_up) override;
    ~Magnum();
};

#endif // MAGNUM_H