#include "projectilelaser.h"

ProjectileLaser::ProjectileLaser(const ProjectileType &t, const TextureFigure &tex, const Hitbox &h, const std::pair<int, int> &d, uint8_t velocity, uint8_t tiles, std::shared_ptr<Dispersion> dispersion) : Projectile(t, tex, h, d, velocity),
                                                                                                                                                                                                              dispersion(dispersion), trayectory(0),
                                                                                                                                                                                                              iterations_left(tiles * TILE_SIZE)
{
    directions = {
        {direction.first, 1},
        {direction.first, -1},
        {0, 1},
        {(direction.first * -1), -1},
        {0, 1}};
}

ProjectileLaser::ProjectileLaser(const ProjectileType &t, const TextureFigure &tex, const Hitbox &h, const std::pair<int, int> &d, uint8_t velocity, uint8_t tiles) : Projectile(t, tex, h, d, velocity),
                                                                                                                                                                      dispersion(nullptr), trayectory(0),
                                                                                                                                                                      iterations_left(tiles * TILE_SIZE)
{
    directions = {
        {direction.first, 1},
        {direction.first, -1},
        {0, 1},
        {(direction.first * -1), -1},
        {0, 1}};
}
void ProjectileLaser::move(const std::function<bool(Position &)> &validator)
{
    if (iterations_left <= 0)
    {
        finish = true;
        return;
    }

    std::pair<int, int> direction_to_move = directions.front();

    if (direction.first != 0)
    {
        int i = 0;

        while (i <= velocity)
        {
            Position new_position(position.x + direction_to_move.first, position.y + direction_to_move.second);
            if (dispersion != nullptr && i == (velocity - 1))
                new_position.y += dispersion->calculate_dispersion(trayectory);
            Position end_hitbox(new_position.x + 8 - 1, new_position.y + 8 - 1);
            if (validator(new_position) && validator(end_hitbox))
                position = new_position;
            else
            {
                directions.erase(directions.begin());
                directions.push_back(direction_to_move);
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
            Position new_position(position.x + direction_to_move.first, position.y + direction_to_move.second);
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

ProjectileLaser::~ProjectileLaser()
{
}
