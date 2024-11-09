#include <cstdint>
#include "projectile.h"

class GrenadeProjectile : public Projectile
{
private:
    uint8_t time_explosion;

public:
    explicit GrenadeProjectile(ProjectileType t, Position p, std::pair<int, int> &d, uint8_t tiles, uint8_t velocity, uint8_t time_explosion) : Projectile(t, p, d, tiles, velocity), time_explosion(time_explosion) {};

    void move()
    {
        if (!time_explosion)
            return;
        position.pos_x += direction.first * velocity;
        position.pos_y += direction.second * velocity;
        time_explosion--;
    }

    void collide_walls()
    {
        direction.first = 0;
        direction.second = -1;
    }

    bool is_finish()
    {
        return !time_explosion;
    }

    ~GrenadeProjectile() {};
};