#include "soundmanager.h"
#include <iostream>

#define MAX_QUANTITY_SOUNDS 3

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

SoundManager::SoundManager(SDL2pp::Mixer &mixer, const int &volume, const TextureFigure &texture) : volume(volume), texture(texture),
                                                                                                    music_box(mixer), current_quantity_sound(0)
{
}

bool SoundManager::listened(uint16_t id)
{
    return ids.find(id) != ids.end();
}

void SoundManager::sound(uint16_t id)
{
    std::cout << "El id es " << (int)id << std::endl;
    if (listened(id) || current_quantity_sound >= MAX_QUANTITY_SOUNDS)
        return;
    music_box.play_sound(volume, texture);
    ids.insert(id);
    current_quantity_sound++;
}

void SoundManager::clear()
{
    current_quantity_sound = 0;
}

SoundManager::~SoundManager()
{
}
