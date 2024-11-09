#include "projectile.h"

class ProjectileGun : public Projectile
{
private:
    uint16_t iterations_left;

public:
    explicit ProjectileGun(ProjectileType t, Position p, std::pair<int, int> &d, uint8_t velocity, uint8_t tiles);
    void move() override;
    void cancel_move() override;
    void collide_walls() override;
    ~ProjectileGun();
};
