#ifndef PROJECTILE_GUN_H
#define PROJECTILE_GUN_H

#include "projectile.h"
#include "../dispersion/dispersion.h"

class ProjectileGun : public Projectile
{
private:
    std::shared_ptr<Dispersion> dispersion;
    uint16_t trayectory;
    uint16_t iterations_left;

public:
    ProjectileGun(const ProjectileType &t, const TextureFigure &tex, const Hitbox &h, const std::pair<int, int> &d, uint8_t velocity, uint8_t tiles, std::shared_ptr<Dispersion> dispersion);
    ProjectileGun(const ProjectileType &t, const TextureFigure &tex, const Hitbox &h, const std::pair<int, int> &d, uint8_t velocity, uint8_t tiles);
    void move(const std::function<bool(Position &)> &validator) override;
    ~ProjectileGun();
};

#endif // PROJECTILE_GUN_H