#include "explosionmanager.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

ExplosionManager::ExplosionManager() : id_explosions(0)
{
}

void ExplosionManager::add_explosion(Explosion &explosion)
{
    explosion.set_id(id_explosions);
    explosions.push_back(explosion);
    id_explosions++;
}

void ExplosionManager::dicrement(const std::function<void(std::shared_ptr<Projectile> &projectile)> &add_projectile, const std::function<void(Hitbox explostion_hitbox)> &check_intersect)
{
    for (auto it = explosions.begin(); it != explosions.end();)
    {
        if (it->is_finish())
        {
            check_intersect(it->get_hitbox());
            it->add_fragments(add_projectile);
            it = explosions.erase(it);
            continue;
        }
        it->time_decrement();
        it++;
    }
}

std::vector<Explosion> &ExplosionManager::get_explosions()
{
    return explosions;
}

std::vector<ExplosionSnapshot> &ExplosionManager::get_status()
{
    explosion_status.clear();
    for (auto &explosion : explosions)
        explosion_status.push_back(explosion.get_status());
    return explosion_status;
}

ExplosionManager::~ExplosionManager()
{
}
