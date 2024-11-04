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

public:
    Gun() : is_equipped(false), rounds(0), shooting(false) {}

    virtual ~Gun() = default;

    void equipped() { is_equipped = true; };

    void dropped() { is_equipped = false; };

    bool has_been_equipped() { return is_equipped; };

    void start_shooting() { shooting = true; }

    void stop_shooting() { shooting = false; }

    virtual ShootEvent shoot(bool &looking_right, bool &looking_up) = 0;

    virtual GunNoEquippedSnapshot get_status() = 0;
};

#endif // SERVER_GUN_H