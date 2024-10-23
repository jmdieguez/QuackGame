#ifndef SERVER_GUN_H
#define SERVER_GUN_H

#include <cstdint>

#include "shoot_event.h"
#include "../../common/gun_dto.h"

class Gun {
protected:
    uint8_t rounds;
    bool shooting;
public:
    Gun() : rounds(0), shooting(false) {}
    
    virtual ~Gun() = default;

    void start_shooting() { shooting = true; }

    void stop_shooting() { shooting = false; }

    virtual ShootEvent shoot() = 0;

    virtual GunDTO get_status() = 0;
};

#endif // SERVER_GUN_H
