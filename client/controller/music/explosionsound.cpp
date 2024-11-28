#include "explosionsound.h"

#define MAX_QUANTITY_SOUNDS 3

ExplosionSound::ExplosionSound(SDL2pp::Mixer &mixer) : current_quantity_sound(0),
                                                       music_box(mixer)
{
}

bool ExplosionSound::listened(uint16_t id)
{
    return ids_explosion.find(id) != ids_explosion.end();
}

void ExplosionSound::sound(uint16_t id)
{
    if (listened(id) || current_quantity_sound >= MAX_QUANTITY_SOUNDS)
        return;
    music_box.play_sound(TextureFigure::ExplosionFigure);
    ids_explosion.insert(id);
    current_quantity_sound++;
}

void ExplosionSound::clear()
{
    current_quantity_sound = 0;
}

ExplosionSound::~ExplosionSound()
{
}