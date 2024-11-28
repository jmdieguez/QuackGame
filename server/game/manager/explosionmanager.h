#ifndef EXPLOSION_MANAGER_H
#define EXPLOSION_MANAGER_H

#include <memory>
#include <cstdint>
#include <vector>

#include "../gun/explosion.h"

class ExplosionManager
{
private:
    uint16_t id_explosions;
    std::vector<Explosion> explosions;
    std::vector<ExplosionSnapshot> explosion_status;

public:
    ExplosionManager();
    void add_explosion(Explosion &explosions);
    void dicrement(const std::function<void(std::shared_ptr<Projectile> &projectile)> &add_projectile, const std::function<void(Hitbox explostion_hitbox)> &check_intersect);
    std::vector<Explosion> &get_explosions();
    std::vector<ExplosionSnapshot> &get_status();
    ~ExplosionManager();
};

#endif // EXPLOSION_MANAGER_H