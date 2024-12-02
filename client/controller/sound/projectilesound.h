#ifndef PROJECTILE_GUN_SOUND_H
#define PROJECTILE_GUN_SOUND_H

#include "soundmanager.h"

class ProjectileGunSound : public SoundManager
{
private:
public:
    explicit ProjectileGunSound(SDL2pp::Mixer &mixer, unsigned &volume);
    ~ProjectileGunSound();
};

#endif // PROJECTILE_GUN_SOUND_H