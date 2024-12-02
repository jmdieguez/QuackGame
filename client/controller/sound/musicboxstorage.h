#ifndef MUSIC_BOX_STORAGE
#define MUSIC_BOX_STORAGE

#include "explosionsound.h"
#include "projectilesound.h"

class MusicBoxStorage
{
private:
    ExplosionSound explosion;
    ProjectileGunSound projectile;

public:
    explicit MusicBoxStorage(SDL2pp::Mixer &mixer);
    ProjectileGunSound &get_projectile_sound();
    ExplosionSound &get_explosion_sound();
    void clear_sounds();
    ~MusicBoxStorage();
};

#endif // MUSIC_BOX_STORAGE