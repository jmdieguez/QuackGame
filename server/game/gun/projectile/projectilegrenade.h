#ifndef PROJECTILE_GRENADE_H
#define PROJECTILE_GRENADE_H

#include "projectile.h"
#include "../dispersion/dispersiongrenade.h"

class ProjectileGrenade : public Projectile
{
private:
    DuckStatus &status;
    const Position &duck_position;
    uint16_t time_to_explosion;
    uint16_t trayectory;
    bool is_throwing;
    bool collide_wall;

    void set_value_explosion();

public:
    explicit ProjectileGrenade(DuckStatus &status, const Position &duck_position);
    void move(const std::function<bool(Position &)> &validator) override;
    void throw_grenade(bool &looking_right);
    Position get_position_to_explosion();
    ~ProjectileGrenade();
};

#endif // PROJECTILE_GRENADE_H