#ifndef GRENADE_H
#define GRENADE_H

#include <utility>
#include <cstdint>
#include "../../../common/position.h"
#include "../../../common/snapshots.h"
#include "projectile/projectile.h"
#include "projectile/projectilegrenade.h"
#include "gun.h"

class Grenade : public Gun
{
private:
    bool start_explosion_state;
    uint8_t time_explosion;
    std::shared_ptr<ProjectileGrenade> projectile_grenade;

public:
    explicit Grenade(const uint16_t &id, const Position &position);
    std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> shoot(DuckStatus &status, const Position &duck_position) override;
    Position get_position_in_duck(const uint16_t &height_duck, const Position &duck, const bool &looking_right, const bool &looking_up) override;
    bool throw_grenade(bool &looking_right);
    ~Grenade();
};

#endif // GRENADE