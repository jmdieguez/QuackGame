#include "projectile.h"

class ProjectileGun : public Projectile
{
private:
    uint16_t iterations_left;

public:
    explicit ProjectileGun(const ProjectileType &t, const Position &p, const std::pair<int, int> &d, uint8_t velocity, uint8_t tiles);
    void move() override;
    void cancel_move() override;
    void collide_walls() override;
    ~ProjectileGun();
};
