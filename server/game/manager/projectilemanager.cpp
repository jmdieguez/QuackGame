#include "projectilemanager.h"

bool ProjectileManager::verify_hit_box(Box &box, const Position &position, std::shared_ptr<Projectile> &projectile, const std::function<void(const Position &, const Position &)> &callable)
{
    Hitbox projectile_hitbox = projectile->get_hitbox();
    Size size(TILE_SIZE, TILE_SIZE);
    Position position_as_pixels(position.x * TILE_SIZE, position.y * TILE_SIZE);
    Hitbox box_hitbox(position_as_pixels, size);
    if (box_hitbox.intersects(projectile_hitbox))
    {
        if (box == Box::BOX_1_HP)
        { // Refactorizar en clase
            callable(position, position_as_pixels);
        }
        else if (box == Box::BOX_2_HP)
        {
            box = Box::BOX_1_HP;
        }
        else if (box == Box::BOX_3_HP)
        {
            box = Box::BOX_2_HP;
        }
        else if (box == Box::BOX_4_HP)
        {
            box = Box::BOX_3_HP;
        }
        projectile->destroy();
        return true;
    }
    return false;
}

bool ProjectileManager::verify_hit_duck(Duck &duck, std::shared_ptr<Projectile> &projectile)
{
    Hitbox projectile_hitbox = projectile->get_hitbox();

    if (projectile->get_type() == ProjectileType::Grenade)
        return false;
    if (projectile->get_type() == ProjectileType::Banana)
    {
        ProjectileBanana *banana = (ProjectileBanana *)projectile.get();
        banana->check_collision(duck.get_hitbox(), duck.get_duck_status());
        return false;
    }

    if (duck.intersects(projectile_hitbox))
    {
        duck.set_receive_shot();
        projectile->destroy();
        return true;
    }
    return false;
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

ProjectileManager::ProjectileManager() : id_projectiles(0)
{
}

void ProjectileManager::add_projectile(const std::shared_ptr<Projectile> &projectile)
{
    projectile->set_id(id_projectiles);
    projectiles.push_back(projectile);
    id_projectiles++;
}

std::vector<std::shared_ptr<Projectile>> &ProjectileManager::get_projectiles()
{
    return projectiles;
}

std::vector<ProjectileSnapshot> &ProjectileManager::get_status()
{
    projectile_status.clear();
    for (auto &projectile : projectiles)
        projectile_status.push_back(projectile->get_status());
    return projectile_status;
}

void ProjectileManager::move(Map &map)
{
    for (std::shared_ptr<Projectile> &p : projectiles)
        p->move([map](Position &p)
                { return map.validate_coordinate(p); });
}

void ProjectileManager::verify_hit(std::map<uint8_t, Duck> &ducks, std::map<Position, Box> &boxes, const std::function<void(const Position &, const Position &)> &callable)
{
    for (std::shared_ptr<Projectile> &p : projectiles)
    {
        bool hit = false;
        for (auto &[id, duck] : ducks)
        {
            if (!duck.is_alive())
                continue;
            if (verify_hit_duck(duck, p))
            {
                hit = true;
                break;
            }
        }

        if (!hit)
        {
            for (auto &[position, box] : boxes)
            {
                if (p->get_type() == ProjectileType::Banana || p->get_type() == ProjectileType::Grenade || verify_hit_box(box, position, p, callable))
                    break;
            }
        }
    }
}

void ProjectileManager::remove(const std::function<void(std::vector<std::shared_ptr<Projectile>>::iterator it)> &add_explosion)
{
    for (auto it = projectiles.begin(); it != projectiles.end();)
    {
        if (it->get()->is_finish())
        {
            if (it->get()->get_type() == ProjectileType::Grenade)
                add_explosion(it);
            it = projectiles.erase(it);
            continue;
        }
        it++;
    }
}

ProjectileManager::~ProjectileManager()
{
}
