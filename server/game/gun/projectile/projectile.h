#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <vector>
#include <cstdint>

#include "../../../../common/projectiletype.h"
#include "../../../../common/projectiledirection.h"
#include "../../../../common/defs.h"
#include "../../../../common/position.h"
#include "../../../../common/snapshots.h"
#include "../../hitbox.h"

class Projectile : public Hitbox
{
private:
    ProjectileType type;
    ProjectileDirection type_direction;

protected:
    uint8_t velocity;
    std::pair<int, int> direction;
    bool finish;

public:
    Projectile(const ProjectileType &t, const Position &p, const std::pair<int, int> &d, uint8_t velocity)
        : Hitbox(p, Size(8, 8)), type(t), velocity(velocity), direction(d), finish(false)
    {
        if (direction.second > 0)
            type_direction = ProjectileDirection::Up;
        else
            type_direction = direction.first == 1 ? ProjectileDirection::Right : ProjectileDirection::Left;
    }

    virtual void move() = 0;

    virtual void cancel_move() = 0;

    virtual bool is_finish() { return finish; };

    virtual void collide_walls() = 0;

    void destroy()
    {
        finish = true;
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
        return ProjectileSnapshot(position.x, position.y, type, type_direction, finish);
    }

    virtual ~Projectile() = default;
};

#endif // PROJECTILE_H