#include <cstdint>
#include "projectile.h"

#define TIME_FIRE 10

class GrenadeProjectile : public Projectile
{
private:
    uint8_t time_explosion;
    uint8_t time_fire;
    bool change_direction;

public:
    explicit GrenadeProjectile(ProjectileType t, Position p, std::pair<int, int> &d, uint8_t tiles, uint8_t velocity, uint8_t time_explosion) : Projectile(t, p, d, tiles, velocity),
                                                                                                                                                time_explosion(time_explosion), time_fire(TIME_FIRE), change_direction(false) {};

    void move()
    {
        if (!time_explosion)
            return;
        position.pos_x += direction.first * velocity;
        position.pos_y += direction.second * velocity;
        time_explosion--;
    }

    uint8_t get_time_fire()
    {
        return time_fire;
    }

    void collide_walls()
    {
        direction.first = 0;
        direction.second = -1;
        change_direction = true;
    }

    void reduce_time()
    {
        time_explosion--;
    }

    bool is_finish()
    {
        return !time_explosion;
    }

    bool is_change_direction_apply()
    {
        return change_direction;
    }

    ~GrenadeProjectile() {};
};