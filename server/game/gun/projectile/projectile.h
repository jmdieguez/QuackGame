#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <vector>
#include <cstdint>
#include <functional>

#include "../../../../common/projectiletype.h"
#include "../../../../common/projectiledirection.h"
#include "../../../../common/defs.h"
#include "../../../../common/position.h"
#include "../../../../common/snapshots.h"
#include "../../hitbox.h"

class Projectile : public Hitbox
{
private:
    uint16_t id;
    ProjectileType type;
    ProjectileDirection type_direction;

protected:
    TextureFigure texture;
    uint8_t velocity;
    std::pair<int, int> direction;
    bool finish;

public:
    Projectile(const ProjectileType &t, const TextureFigure &tex, const Hitbox &h, const std::pair<int, int> &d, uint8_t velocity)
        : Hitbox(h), type(t), texture(tex), velocity(velocity), direction(d), finish(false)
    {
        if (direction.second > 0)
            type_direction = ProjectileDirection::Up;
        else
            type_direction = direction.first == 1 ? ProjectileDirection::Right : ProjectileDirection::Left;
    }

    Projectile(const ProjectileType &t, const TextureFigure &tex, uint8_t velocity)
        : Hitbox(Position(0, 0), Size(0, 0)), type(t), texture(tex), velocity(velocity), finish(false) {}

    virtual void move(const std::function<bool(Position &)> &validator) = 0;

    virtual bool is_finish() { return finish; };

    void destroy()
    {
        finish = true;
    }

    void set_id(uint16_t value)
    {
        id = value;
    }

    Position get_position()
    {
        return position;
    }

    ProjectileType get_type()
    {
        return type;
    }

    ProjectileSnapshot get_status()
    {
        return ProjectileSnapshot(id, position.x, position.y, type, texture, type_direction);
    }

    uint8_t get_velocity()
    {
        return velocity;
    }

    virtual ~Projectile() = default;
};

#endif // PROJECTILE_H