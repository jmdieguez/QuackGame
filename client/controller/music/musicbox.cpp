#include "musicbox.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

MusicBox::MusicBox(SDL2pp::Mixer &mixer) : mixer(mixer)
{
}

void MusicBox::play_sound(const TextureFigure &texture)
{
    SDL2pp::Chunk &sound = get_chunk(texture);
    sound.SetVolume(1);
    mixer.PlayChannel(-1, sound);
}

MusicBox::~MusicBox()
{
}
