#ifndef PROJECTILE_GUN_SOUND_H
#define PROJECTILE_GUN_SOUND_H

#include <set>
#include "musicbox.h"
#include <cstdint>

class ProjectileGunSound
{
private:
    std::set<uint16_t> ids_projectile;
    uint16_t current_quantity_sound;
    MusicBox music_box;

public:
    explicit ProjectileGunSound(SDL2pp::Mixer &mixer);
    bool listened(uint16_t id);
    void sound(uint16_t id);
    void clear();
    ~ProjectileGunSound();
};

#endif // PROJECTILE_GUN_SOUND_H