#ifndef SOUND_BOX_STORAGE
#define SOUND_BOX_STORAGE

#include "explosionsound.h"
#include "projectilesound.h"
#include "projectilelasersound.h"
#include "../../../common/config.h"

class SoundBoxStorage
{
private:
    unsigned volume_explosion;
    unsigned volume_projectile;
    unsigned volume_projectile_laser;
    ExplosionSound explosion;
    ProjectileGunSound projectile;
    ProjectileLaserSound projectile_laser;

public:
    explicit SoundBoxStorage(SDL2pp::Mixer &mixer);
    ProjectileGunSound &get_projectile_sound();
    ExplosionSound &get_explosion_sound();
    ProjectileLaserSound &get_projectile_laser_sound();
    void clear_sounds();
    ~SoundBoxStorage();
};

#endif // SOUND_BOX_STORAGE