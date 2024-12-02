#include "musicboxstorage.h"

MusicBoxStorage::MusicBoxStorage(SDL2pp::Mixer &mixer) : explosion(mixer), projectile(mixer)
{
}

ProjectileGunSound &MusicBoxStorage::get_projectile_sound()
{
    return projectile;
}

ExplosionSound &MusicBoxStorage::get_explosion_sound()
{
    return explosion;
}

void MusicBoxStorage::clear_sounds()
{
    projectile.clear();
    explosion.clear();
}

MusicBoxStorage::~MusicBoxStorage()
{
}
