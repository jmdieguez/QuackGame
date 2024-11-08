#include <vector>
#include <cstdint>

#include "../../../common/projectiletype.h"
#include "../../../common/projectiledirection.h"
#include "../../../common/defs.h"
#include "../../../common/position.h"

class Projectile
{
private:
    ProjectileType type;
    ProjectileDirection type_direction;
    Position position;
    std::pair<int, int> direction;
    uint8_t iterations_left = 0;
    uint8_t velocity;
    bool finish;

public:
    Projectile(ProjectileType t, Position p, std::pair<int, int> &d, uint8_t tiles, uint8_t velocity)
        : type(t), position(p), direction(d), iterations_left(tiles * TILE_SIZE), velocity(velocity), finish(false)
    {
        if (direction.second > 0)
            type_direction = ProjectileDirection::Up;
        else
            type_direction = direction.first == 1 ? ProjectileDirection::Right : ProjectileDirection::Left;
    }

    void move()
    {
        if (iterations_left <= 0)
            return;
        position.pos_x += direction.first * velocity;
        position.pos_y += direction.second * velocity;
        iterations_left -= velocity;
        if (iterations_left <= 0)
            finish = true;
    }

    void cancel_move()
    {
        position.pos_x -= direction.first * velocity;
        position.pos_y -= direction.second * velocity;
    }

    bool is_finish()
    {
        return finish;
    }

    void destroy()
    {
        finish = true;
    }

    Position &get_position()
    {
        return position;
    }

    ProjectileType get_type()
    {
        return type;
    }

    ProjectileSnapshot get_status()
    {
        return ProjectileSnapshot(position.pos_x, position.pos_y, type, type_direction, finish);
    }
    ~Projectile() {}
};
