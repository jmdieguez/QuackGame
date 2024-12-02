#ifndef EXPLOSION_SOUND_H
#define EXPLOSION_SOUND_H

#include "soundmanager.h"

class ExplosionSound : public SoundManager
{
private:
public:
    explicit ExplosionSound(SDL2pp::Mixer &mixer);
    ~ExplosionSound();
};

#endif // EXPLOSION_SOUND_H