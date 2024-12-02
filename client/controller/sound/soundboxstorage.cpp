#include "soundboxstorage.h"

SoundBoxStorage::SoundBoxStorage(SDL2pp::Mixer &mixer) :

                                                         volume_explosion(Config::getInstance()["effect"]["type"]["explosion"].as<unsigned>()),
                                                         volume_projectile(Config::getInstance()["effect"]["type"]["projectile_gun"].as<unsigned>()),
                                                         volume_projectile_laser(Config::getInstance()["effect"]["type"]["laser"].as<unsigned>()),
                                                         explosion(mixer, volume_explosion), projectile(mixer, volume_projectile),
                                                         projectile_laser(mixer, volume_projectile_laser)
{
}

ProjectileGunSound &SoundBoxStorage::get_projectile_sound()
{
    return projectile;
}

ProjectileLaserSound &SoundBoxStorage::get_projectile_laser_sound()
{
    return projectile_laser;
}

ExplosionSound &SoundBoxStorage::get_explosion_sound()
{
    return explosion;
}

void SoundBoxStorage::clear_sounds()
{
    projectile.clear();
    explosion.clear();
    projectile_laser.clear();
}

SoundBoxStorage::~SoundBoxStorage()
{
}
