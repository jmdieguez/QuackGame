#include "musicboxstorage.h"

MusicBoxStorage::MusicBoxStorage(SDL2pp::Mixer &mixer) : projectile(mixer)
{
}

ProjectileGunSound &MusicBoxStorage::get_projectile_sound()
{
    return projectile;
}

void MusicBoxStorage::clear_sounds()
{
    projectile.clear();
}

MusicBoxStorage::~MusicBoxStorage()
{
}
