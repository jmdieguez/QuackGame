#ifndef GUN_AMMO_H
#define GUN_AMMO_H

#include <cstdint>

class GunAmmo
{
private:
    uint8_t ammo;

protected:
    void reduce_ammo()
    {
        if (ammo > 0)
            ammo--;
    }

public:
    explicit GunAmmo(uint8_t ammo) : ammo(ammo) {};
    bool have_ammo()
    {
        return ammo > 0;
    };
    ~GunAmmo() {};
};

#endif // GUN_AMMO_H