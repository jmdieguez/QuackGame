#include "projectilegun.h"

ProjectileGun::ProjectileGun(const ProjectileType &t, const Position &p, const std::pair<int, int> &d, uint8_t velocity, uint8_t tiles) : Projectile(t, p, d, velocity),
                                                                                                                                          iterations_left(tiles * TILE_SIZE)
{
}

void ProjectileGun::move()
{

    if (iterations_left <= 0)
        return;
    position.x += direction.first * velocity;
    position.y += direction.second * velocity;
    iterations_left -= velocity;
    if (iterations_left <= 0)
        finish = true;
}

void ProjectileGun::cancel_move()
{
    position.x -= direction.first * velocity;
    position.y -= direction.second * velocity;
}

void ProjectileGun::collide_walls()
{
}

ProjectileGun::~ProjectileGun()
{
}
