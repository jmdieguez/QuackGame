#ifndef SERVER_GUN_H
#define SERVER_GUN_H

#include <cstdint>
#include <vector>
#include <optional>
#include <memory>

#include "../../../common/snapshots.h"
#include "../../../common/texturesize.h"
#include "../../../common/projectiletype.h"
#include "../../../common/position.h"
#include "../../../common/size.h"
#include "projectile/projectile.h"

class Gun
{
private:
    GunType type;
    bool is_equipped;
    Size size;

protected:
    Position position;

    std::pair<int, int> get_directions(bool looking_right, bool looking_up)
    {
        int direction_x = looking_right ? 1 : -1;
        int direction_y = looking_up ? -1 : 0;
        if (looking_up)
            direction_x = 0;
        return {direction_x, direction_y};
    }

public:
    explicit Gun(GunType type, Position p, Size size) : type(type), is_equipped(false), size(size), position(p) {}

    virtual ~Gun() = default;

    void equipped() { is_equipped = true; };

    void dropped() { is_equipped = false; };

    bool has_been_equipped() { return is_equipped; };

    bool can_take_this_gun(const Position &duck_position) const
    {
        return ((duck_position.x - GUN_WIDTH) == position.x || (duck_position.x + GUN_WIDTH) == position.x) && duck_position.y == position.y;
    }

    GunNoEquippedSnapshot get_status()
    {
        return GunNoEquippedSnapshot(type, position);
    }

    GunType get_type()
    {
        return type;
    }

    virtual std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> shoot(bool &looking_right, bool &looking_up, const Position &duck_position) = 0;
};

#endif // SERVER_GUN_H