#include "projectilegun.h"

ProjectileGun::ProjectileGun(const ProjectileType &t, const Position &p, const std::pair<int, int> &d, uint8_t velocity, uint8_t tiles, std::shared_ptr<Dispersion> dispersion) : Projectile(t, p, d, velocity),
                                                                                                                                                                                  dispersion(dispersion), trayectory(0), iterations_left(tiles * TILE_SIZE)
{
}

ProjectileGun::ProjectileGun(const ProjectileType &t, const Position &p, const std::pair<int, int> &d, uint8_t velocity, uint8_t tiles) : Projectile(t, p, d, velocity),
                                                                                                                                          dispersion(nullptr), trayectory(0), iterations_left(tiles * TILE_SIZE)
{
}

void ProjectileGun::move()
{

    if (iterations_left <= 0)
        return;

    if (dispersion != nullptr)
    {
        if (direction.first != 0)
        {
            position.x += direction.first * velocity;
            position.y += dispersion->calculate_dispersion(trayectory);
        }
        if (direction.second == -1)
        {
            position.y += direction.second * velocity;
            position.x += dispersion->calculate_dispersion(trayectory);
        }
    }
    else
    {
        position.x += direction.first * velocity;
        position.y += direction.second * velocity;
    }
    iterations_left -= velocity;
    trayectory++;
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
