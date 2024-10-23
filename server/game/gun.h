#ifndef SERVER_GUN_H
#define SERVER_GUN_H

#include <cstdint>

#include "shoot_event.h"
#include "../../common/snapshots.h"

class Gun {
protected:
    uint8_t rounds;
    bool shooting;
public:
    Gun() : rounds(0), shooting(false) {}
    
    virtual ~Gun() = default;

    void start_shooting() { shooting = true; }

    void stop_shooting() { shooting = false; }

    virtual ShootEvent shoot(bool &looking_right, bool &looking_up) = 0;

    virtual GunSnapshot get_status() = 0;
};

#endif // SERVER_GUN_H
