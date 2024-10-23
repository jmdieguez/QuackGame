#ifndef SHOOT_EVENT_H
#define SHOOT_EVENT_H

#include <vector>
#include <cstdint>

enum class ProjectileType {
    None = 0,
    ChainBullet,
    Grenade,
    PeeledBanana,
    Laser,
    ShotgunShell,
    MagnumShell,
    PistolShell,
};

class Projectile {
private:
    ProjectileType type;
    std::pair<uint16_t, uint16_t> position;
    std::pair<uint8_t, uint8_t> direction;
public:
    Projectile(ProjectileType &t, std::pair<uint16_t, uint16_t> &p, std::pair<uint8_t, uint8_t> &d)
        : type(t), position(p), direction(d) {}
};

class ShootEvent {
private:
    uint8_t iterations_left = 0;
    std::vector<Projectile> projectiles;
public:
    ShootEvent() {}
    ~ShootEvent() {}

    void add_projectile(Projectile &p) {
        projectiles.push_back(p);
    }
};

#endif // SHOOT_EVENT_H
