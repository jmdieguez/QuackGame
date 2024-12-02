#ifndef PROJECTILE_LASER_SOUND_H
#define PROJECTILE_LASER_SOUND_H

#include "soundmanager.h"

class ProjectileLaserSound : public SoundManager
{
private:
public:
    explicit ProjectileLaserSound(SDL2pp::Mixer &mixer, unsigned &volume);
    ~ProjectileLaserSound();
};

#endif // PROJECTILE_LASER_SOUND_H