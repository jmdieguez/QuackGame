#ifndef PEW_PEW_LASER_H
#define PEW_PEW_LASER_H

#include "gun.h"
#include "gunammo.h"
#include "dispersion/dispersionhigh.h"
#include "positiongun.h"

class PewPewLaser : public Gun, public GunAmmo
{
private:
    PositionGun position_gun;

public:
    explicit PewPewLaser(const uint16_t &id, const Position &position);
    std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> shoot(DuckStatus &status, const Position &duck_position) override;
    Position get_position_in_duck(const uint16_t &height_duck, const Position &duck, const bool &looking_right, const bool &looking_up) override;
    ~PewPewLaser();
};

#endif // PEW_PEW_LASER