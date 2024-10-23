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
public:
    const GunType type;
    const uint8_t rounds;

    GunDTO(GunType &t, uint8_t &r) : type(t), rounds(r) {}
};

#endif // COMMON_GUN_DTO_H
