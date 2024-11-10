#ifndef COWBOY_PISTOL_H
#define COWBOY_PISTOL_H

#include "gun.h"
#include "gunammo.h"

class CowboyPistol : public Gun, public GunAmmo
{
private:
public:
    explicit CowboyPistol(const uint16_t &pos_x, const uint16_t &pos_y);
    std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> shoot(bool &looking_right, bool &looking_up, const Position &duck_position) override;
    Position get_position_in_duck(const uint16_t &height_duck, const Position &duck, const bool &looking_right) override;
    ~CowboyPistol();
};

#endif // COWBOY_PISTOL_H