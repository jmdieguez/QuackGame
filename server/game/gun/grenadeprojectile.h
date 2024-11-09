#include <cstdint>
#include "projectile.h"

class GrenadeProjectile : public Projectile
{
private:
    uint8_t time_explosion;

public:
    explicit GrenadeProjectile(ProjectileType t, Position p, std::pair<int, int> &d, uint8_t tiles, uint8_t velocity, uint8_t time_explosion) : Projectile(t, p, d, tiles, velocity), time_explosion(time_explosion) {};
    ~GrenadeProjectile() {};
};