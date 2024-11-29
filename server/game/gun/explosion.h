#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <memory>
#include <utility>

#include "projectile/projectilegun.h"
#include "../../../common/size.h"
#include "../../../common/snapshots.h"
#include "../../../common/position.h"
#include "../../../common/texturefigure.h"

#define WIDTH_EXPLOSION 40
#define HEIGHT_EXPLOSION 40
#define TIME_EXPLOSION 10

#define VELOCITY 10
#define MAX_DISTANCE 5

#define PROJECTILE_WIDTH 8
#define PROJECTILE_HEIGHT 8

class Explosion : public Hitbox
{
private:
    uint16_t id;
    uint8_t time;

public:
    explicit Explosion(const Position &position) : Hitbox(position, Size(WIDTH_EXPLOSION, HEIGHT_EXPLOSION)), time(TIME_EXPLOSION) {};
    ExplosionSnapshot get_status()
    {
        return ExplosionSnapshot(id, position, TextureFigure::ExplosionFigure);
    };
    void time_decrement()
    {
        if (!time)
            return;
        time--;
    }

    bool is_finish()
    {
        return !time;
    }

    void set_id(uint16_t value)
    {
        id = value;
    }

    void add_fragments(const std::function<void(std::shared_ptr<Projectile> &projectile)> &add_projectile)
    {
        std::vector<std::pair<int, int>> directions = {std::make_pair(-1, 0), std::make_pair(1, 0)};
        uint16_t x = position.x + size.width / 2;
        uint16_t y = position.y + size.height / 2;
        Hitbox hitbox_projectile(Position(x, y), Size(PROJECTILE_WIDTH, PROJECTILE_HEIGHT));
        for (std::pair<int, int> direction : directions)
        {
            std::shared_ptr<Projectile> projectile = std::make_shared<ProjectileGun>(ProjectileType::CowboyBullet, TextureFigure::CowboyBullet, hitbox_projectile, direction, VELOCITY, MAX_DISTANCE);
            add_projectile(projectile);
        }
    };

    ~Explosion() {};
};

#endif // EXPLOSION_H