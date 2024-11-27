#include "projectilegun.h"

ProjectileGun::ProjectileGun(const ProjectileType &t, const TextureFigure &tex, const Hitbox &h, const std::pair<int, int> &d, uint8_t velocity, uint8_t tiles, std::shared_ptr<Dispersion> dispersion) : Projectile(t, tex, h, d, velocity),
                                                                                                                                                                                                          dispersion(dispersion), trayectory(0),
                                                                                                                                                                                                          iterations_left(tiles * TILE_SIZE)
{
}

ProjectileGun::ProjectileGun(const ProjectileType &t, const TextureFigure &tex, const Hitbox &h, const std::pair<int, int> &d, uint8_t velocity, uint8_t tiles) : Projectile(t, tex, h, d, velocity),
                                                                                                                                                                  dispersion(nullptr), trayectory(0),
                                                                                                                                                                  iterations_left(tiles * TILE_SIZE)
{
}
void ProjectileGun::move(const std::function<bool(Position &)> &validator)
{
    if (iterations_left <= 0)
    {
        finish = true;
        return;
    }

    if (direction.second != -1)
    {
        int i = 0;

        while (i <= velocity)
        {
            Position new_position(position.x + direction.first, position.y);
            if (dispersion != nullptr && i == (velocity - 1))
                new_position.y += dispersion->calculate_dispersion(trayectory);
            Position end_hitbox(new_position.x + 8 - 1, new_position.y + 8 - 1);
            if (validator(new_position) && validator(end_hitbox))
                position = new_position;
            else
            {
                finish = true;
                break;
            }
            i++;
        }

        if (finish)
            return;
    }

    if (direction.second == -1)
    {

        int i = 0;

        while (i <= velocity)
        {
            Position new_position(position.x, position.y + direction.second);
            if (dispersion != nullptr && i == (velocity - 1))
                new_position.x += dispersion->calculate_dispersion(trayectory);
            Position end_hitbox(new_position.x + 8 - 1, new_position.y + 8 - 1);
            if (validator(new_position) && validator(end_hitbox))
                position = new_position;
            else
            {
                finish = true;
                break;
            }
            i++;
        }
    }
    iterations_left -= velocity;
    trayectory++;
}

ProjectileGun::~ProjectileGun()
{
}
