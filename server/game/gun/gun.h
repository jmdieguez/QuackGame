#ifndef SERVER_GUN_H
#define SERVER_GUN_H

#include <cstdint>
#include <vector>
#include <optional>
#include <memory>
#include "../../../common/snapshots.h"
#include "../../../common/projectiletype.h"
#include "../../../common/position.h"
#include "../../../common/size.h"
#include "../../../common/texturefigure.h"
#include "../../../common/duck.h"
#include "../hitbox.h"
#include "../duck/defs.h"
#include "projectile/projectile.h"

#define ANGLE_LOOK_UP 90
#define ANGLE_LOOK_UP_REVERSE 270
#define ANGLE_DEFAULT 0

class Gun : public Hitbox
{
private:
    uint16_t id;
    GunType type;
    bool is_equipped;
    uint16_t angle;
    TextureFigure texture;
    bool picked_up_once = false;

protected:
    std::pair<int, int> get_direction(bool looking_right, bool looking_up)
    {
        int direction_x = looking_right ? 1 : -1;
        int direction_y = looking_up ? -1 : 0;
        return {direction_x, direction_y};
    }

public:
    explicit Gun(const uint16_t &id, const GunType &type, const Position &p, const Size &size, const TextureFigure &texture) : Hitbox(p, size), id(id),
                                                                                                                               type(type), is_equipped(false),
                                                                                                                               angle(ANGLE_DEFAULT),
                                                                                                                               texture(texture) {}

    virtual ~Gun() = default;

    void equipped()
    {
        is_equipped = true;
    }

    void dropped(const Position duck)
    {
        picked_up_once = true;
        is_equipped = false;
        position.x = duck.x;
        position.y = duck.y - size.height;
    }

    bool has_been_picked_up() const { return picked_up_once; }

    bool has_been_equipped() { return is_equipped; }

    void change_to_look_up()
    {
        angle = ANGLE_LOOK_UP;
    }

    void reverse_look_up()
    {
        angle = ANGLE_DEFAULT;
    }

    bool can_take_this_gun(const Position &duck_position) const
    {
        return ((duck_position.x - size.width) == position.x || (duck_position.x + size.width) == position.x) && duck_position.y == position.y;
    }

    uint16_t get_angle(const bool &looking_right, const bool &looking_up)
    {
        if (!looking_up)
            return ANGLE_DEFAULT;
        if (looking_right && looking_up)
            return ANGLE_LOOK_UP_REVERSE;
        return ANGLE_LOOK_UP;
    }

    uint16_t get_id()
    {
        return id;
    }

    Size get_size()
    {
        return size;
    }

    void move(const std::function<bool(Position &)> &validator)
    {
        if (picked_up_once)
        {
            int i = 0;
            while (i <= 1)
            {
                Position new_position(position.x, position.y + 1);
                Position end_hitbox(new_position.x + size.width - 1, new_position.y + size.height - 1);
                if (validator(new_position) && validator(end_hitbox))
                {
                    position = new_position;
                    i++;
                }
                else
                {
                    break;
                }
            }
        }
    }

    GunNoEquippedSnapshot get_status()
    {
        return GunNoEquippedSnapshot(texture, position, angle);
    }

    GunType get_type()
    {
        return type;
    }

    TextureFigure get_texture()
    {
        return texture;
    }

    virtual Position get_position_in_duck(const uint16_t &height_duck, const Position &duck, const bool &looking_right, const bool &looking_up) = 0;

    virtual std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> shoot(DuckStatus &status, const Position &duck_position) = 0;
};

#endif // SERVER_GUN_H