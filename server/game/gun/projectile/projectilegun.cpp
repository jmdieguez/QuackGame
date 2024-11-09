#include "projectilegun.h"

ProjectileGun::ProjectileGun(ProjectileType t, Position p, std::pair<int, int> &d, uint8_t velocity, uint8_t tiles) : Projectile(t, p, d, velocity),
                                                                                                                      iterations_left(tiles * TILE_SIZE)
{
}

void ProjectileGun::move()
{

    if (iterations_left <= 0)
        return;
    position.pos_x += direction.first * velocity;
    position.pos_y += direction.second * velocity;
    iterations_left -= velocity;
    if (iterations_left <= 0)
        finish = true;
}

void ProjectileGun::cancel_move()
{
    position.pos_x -= direction.first * velocity;
    position.pos_y -= direction.second * velocity;
}

void ProjectileGun::collide_walls()
{
}

ProjectileGun::~ProjectileGun()
{
}
