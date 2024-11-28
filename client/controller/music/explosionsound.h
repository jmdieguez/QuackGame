#ifndef EXPLOSION_SOUND_H
#define EXPLOSION_SOUND_H

#include <set>
#include <cstdint>
#include "musicbox.h"

class ExplosionSound
{
private:
    std::set<uint16_t> ids_projectile;
    uint16_t current_quantity_sound;
    MusicBox music_box;

public:
    explicit ExplosionSound(SDL2pp::Mixer &mixer);
    bool listened(uint16_t id);
    void sound(uint16_t id);
    void clear();
    ~ExplosionSound();
};

#endif // EXPLOSION_SOUND_H