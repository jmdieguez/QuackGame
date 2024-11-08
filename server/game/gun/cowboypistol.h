#ifndef COWBOY_PISTOL_H
#define COWBOY_PISTOL_H

#include "gun.h"
#include "gunammo.h"

class CowboyPistol : public Gun, public GunAmmo
{
private:
public:
    explicit CowboyPistol(uint16_t pos_x, uint16_t pos_y);
    std::optional<std::pair<std::vector<Projectile>, Position>> shoot(bool &looking_right, bool &looking_up, const Position &duck_position) override;
    ~CowboyPistol();
};

#endif // COWBOY_PISTOL_H