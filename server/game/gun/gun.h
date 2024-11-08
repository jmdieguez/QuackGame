#ifndef SERVER_GUN_H
#define SERVER_GUN_H

#include <cstdint>
#include <optional>

#include "../../../common/snapshots.h"
#include "../../../common/texturesize.h"
#include "../../../common/projectiletype.h"
#include "../../../common/position.h"
#include "projectile.h"

class Gun
{
private:
    GunType type;
    bool is_equipped;
    uint16_t pos_x;
    uint16_t pos_y;

protected:
    bool shooting;

    std::pair<int, int> getDirections(bool looking_right, bool looking_up)
    {
        int direction_x = looking_right ? 1 : -1;
        int direction_y = looking_up ? -1 : 0;
        if (looking_up)
            direction_x = 0;
        return {direction_x, direction_y};
    }

public:
    explicit Gun(GunType type, uint16_t pos_x,
                 uint16_t pos_y) : type(type), is_equipped(false), pos_x(pos_x), pos_y(pos_y), shooting(false) {}

    virtual ~Gun() = default;

    void equipped() { is_equipped = true; };

    void dropped() { is_equipped = false; };

    bool has_been_equipped() { return is_equipped; };

    void start_shooting() { shooting = true; }

    void stop_shooting() { shooting = false; }

    bool can_take_this_gun(uint16_t duck_pos_x, uint16_t duck_pos_y)
    {
        return ((duck_pos_x - GUN_WIDTH) == pos_x || (duck_pos_x + GUN_WIDTH) == pos_x) && duck_pos_y == pos_y;
    }

    GunNoEquippedSnapshot get_status()
    {
        return GunNoEquippedSnapshot(type, pos_x, pos_y);
    }

    GunType get_type()
    {
        return type;
    }

    virtual std::optional<std::pair<Projectile, Position>> shoot(bool &looking_right, bool &looking_up, const Position &duck_position) = 0;
};

#endif // SERVER_GUN_H