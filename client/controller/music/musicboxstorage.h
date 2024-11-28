#ifndef MUSIC_BOX_STORAGE
#define MUSIC_BOX_STORAGE

#include "projectilesound.h"

class MusicBoxStorage
{
private:
    ProjectileGunSound projectile;

public:
    explicit MusicBoxStorage(SDL2pp::Mixer &mixer);
    ProjectileGunSound &get_projectile_sound();
    void clear_sounds();
    ~MusicBoxStorage();
};

#endif // MUSIC_BOX_STORAGE