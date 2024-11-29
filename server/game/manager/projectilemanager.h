#ifndef PROJECTILE_MANAGER_H
#define PROJECTILE_MANAGER_H

#include <memory>
#include <vector>
#include <cstdint>
#include "../map.h"
#include "../duck/duck.h"
#include "../gun/explosion.h"
#include "../gun/projectile/projectile.h"
#include "../../../common/snapshots.h"

class ProjectileManager
{
private:
    uint16_t id_projectiles;
    std::vector<std::shared_ptr<Projectile>> projectiles;
    std::vector<ProjectileSnapshot> projectile_status;

    bool verify_hit_box(Box &box, const Position &position, std::shared_ptr<Projectile> &projectile, const std::function<void(const Position &, const Position &)> &spawn_gun);
    bool verify_hit_duck(Duck &duck, std::shared_ptr<Projectile> &projectile);

public:
    ProjectileManager();
    void add_projectile(const std::shared_ptr<Projectile> &projectiles);
    std::vector<std::shared_ptr<Projectile>> &get_projectiles();
    void move(Map &map);
    void remove(const std::function<void(std::vector<std::shared_ptr<Projectile>>::iterator it)> &add_explosion);
    void verify_hit(std::map<uint8_t, Duck> &ducks, std::map<Position, Box> &boxes, const std::function<void(const Position &, const Position &)> &spawn_gun);
    std::vector<ProjectileSnapshot> &get_status();
    ~ProjectileManager();
};

#endif // PROJECTILE_MANAGER_H