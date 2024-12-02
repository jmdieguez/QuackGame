#include "soundboxstorage.h"

SoundBoxStorage::SoundBoxStorage(SDL2pp::Mixer &mixer) : explosion(mixer), projectile(mixer)
{
}

ProjectileGunSound &SoundBoxStorage::get_projectile_sound()
{
    return projectile;
}

ExplosionSound &SoundBoxStorage::get_explosion_sound()
{
    return explosion;
}

void SoundBoxStorage::clear_sounds()
{
    projectile.clear();
    explosion.clear();
}

SoundBoxStorage::~SoundBoxStorage()
{
}
