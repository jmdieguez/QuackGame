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
    for (int i = 0; i < 8; i++)
    {
        if (mixer.IsChannelPlaying(i))
            continue;
        mixer.PlayChannel(i, sound);
        break;
    }
}

MusicBox::~MusicBox()
{
}
