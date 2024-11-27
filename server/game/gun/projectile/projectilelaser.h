#ifndef PROJECTILE_LASER_H
#define PROJECTILE_LASER_H

#include "projectile.h"
#include "../dispersion/dispersion.h"

class ProjectileLaser : public Projectile
{
private:
    std::shared_ptr<Dispersion> dispersion;
    uint16_t trayectory;
    uint16_t iterations_left;
    std::vector<std::pair<int, int>> directions;
    uint16_t times_to_collide_wall;

    void set_directions();

public:
    ProjectileLaser(const ProjectileType &t, const TextureFigure &tex, const Hitbox &h, const std::pair<int, int> &d, uint8_t velocity, uint8_t tiles, std::shared_ptr<Dispersion> dispersion);
    ProjectileLaser(const ProjectileType &t, const TextureFigure &tex, const Hitbox &h, const std::pair<int, int> &d, uint8_t velocity, uint8_t tiles);
    void move(const std::function<bool(Position &)> &validator) override;
    ~ProjectileLaser();
};

#endif // PROJECTILE_LASER_H