#ifndef SOUND_BOX_STORAGE
#define SOUND_BOX_STORAGE

#include "explosionsound.h"
#include "projectilesound.h"

class SoundBoxStorage
{
private:
    ExplosionSound explosion;
    ProjectileGunSound projectile;

public:
    explicit SoundBoxStorage(SDL2pp::Mixer &mixer);
    ProjectileGunSound &get_projectile_sound();
    ExplosionSound &get_explosion_sound();
    void clear_sounds();
    ~SoundBoxStorage();
};

#endif // SOUND_BOX_STORAGE