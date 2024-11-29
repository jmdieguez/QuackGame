#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <set>
#include <cstdint>

#include "musicbox.h"
#include "../../../common/texturefigure.h"

class SoundManager
{
private:
    int volume;
    TextureFigure texture;
    std::set<uint16_t> ids;
    MusicBox music_box;
    uint16_t current_quantity_sound;

public:
    explicit SoundManager(SDL2pp::Mixer &mixer, const int &volume, const TextureFigure &texture);
    bool listened(uint16_t id);
    void sound(uint16_t id);
    void clear();
    ~SoundManager();
};

#endif // SOUND_MANAGER_H