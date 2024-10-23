#ifndef COMMON_GUN_DTO_H
#define COMMON_GUN_DTO_H

#include <cstdint>

enum class GunType {
    None = 0,
    Shotgun,
    Banana,
    Granade,
    DuelingPistol,
    CowboyPistol,
    Magnum,
    Sniper,
    AK47,
    LaserRifle,
    PewPewLaser
};

class GunDTO {
private:
    GunType type;
    uint8_t rounds;
};

#endif // COMMON_GUN_DTO_H
