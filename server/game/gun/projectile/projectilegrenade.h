#include "projectile.h"

class ProjectileGrenade : public Projectile
{
private:
    uint16_t time_to_explosion;
    uint16_t time_fire;
    bool change_direction;

public:
    explicit ProjectileGrenade(ProjectileType t, Position p, std::pair<int, int> &d, uint8_t velocity);

    void move() override;
    void cancel_move() override;
    void collide_walls() override;

    void reduce_time();
    bool is_change_direction_apply();
    uint8_t get_time_fire();

    ~ProjectileGrenade();
};