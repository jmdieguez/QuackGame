#ifndef SERVER_GUN_H
#define SERVER_GUN_H

#include <cstdint>

#include "../../../common/snapshots.h"
#include "../../../common/texturesize.h"
#include "../../../common/projectiletype.h"
#include "../../../common/position.h"
#include "../projectile.h"

class Gun
{
private:
    bool is_equipped;

protected:
    uint8_t rounds;
    bool shooting;
    uint16_t pos_x;
    uint16_t pos_y;

public:
    Gun() : is_equipped(false), rounds(0), shooting(false), pos_x(0), pos_y(0) {}

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

    virtual Projectile shoot(bool &looking_right, bool &looking_up, Position &duck_position) = 0;

    virtual GunNoEquippedSnapshot get_status() = 0;

    virtual bool have_ammo() = 0;

    virtual GunType get_type() = 0;
};

#endif // SERVER_GUN_H