#include <vector>
#include <cstdint>
// #include "map.h"
#include "../../common/projectiletype.h"
#include "../../common/projectiledirection.h"
#include "../../common/defs.h"
#include "../../common/position.h"

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
        type_direction = direction.first == 1 ? ProjectileDirection::Right : ProjectileDirection::Left;
        if (direction.second)
            type_direction = ProjectileDirection::Up;
    }

    void move()
    {
        if (iterations_left <= 0)
            return;
        position.pos_x += direction.first * velocity;
        position.pos_y += direction.second * velocity;
        // if (map.validate_coordinate(position))
        //     iterations_left--;
        iterations_left -= velocity;
        // iterations_left = 0;
        if (iterations_left <= 0)
            finish = true;
    }

    bool is_finish()
    {
        return finish;
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
