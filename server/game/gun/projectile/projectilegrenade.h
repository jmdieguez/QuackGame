#include "projectile.h"
#include "../dispersion/dispersiongrenade.h"

class ProjectileGrenade : public Projectile
{
private:
    uint16_t time_to_explosion;
    uint16_t time_fire;
    uint16_t trayectory;
    bool collide_wall;

public:
    explicit ProjectileGrenade(const Hitbox &h, const std::pair<int, int> &d);

    void move(const std::function<bool(Position &)> &validator) override;
    void cancel_move() override;
    void collide_walls() override;

    void reduce_time();
    uint8_t get_time_fire() const;

    ~ProjectileGrenade();
};