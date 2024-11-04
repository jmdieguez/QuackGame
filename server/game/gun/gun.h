#ifndef SERVER_GUN_H
#define SERVER_GUN_H

#include <cstdint>

#include "../shoot_event.h"
#include "../../../common/snapshots.h"

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

    bool can_take_this_gun(uint16_t pos_x, uint16_t pos_y)
    {
        return ((pos_x - 32) == this->pos_x || (pos_x + 32) == this->pos_x) && pos_y == this->pos_y;
    }

    uint16_t get_pos_x()
    {
        return pos_x;
    }

    uint16_t get_pos_y() { return pos_y; }

    virtual ShootEvent shoot(bool &looking_right, bool &looking_up) = 0;

    virtual GunNoEquippedSnapshot get_status() = 0;
};

#endif // SERVER_GUN_H