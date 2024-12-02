#include "soundbox.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

SoundBox::SoundBox(SDL2pp::Mixer &mixer) : mixer(mixer)
{
}

void SoundBox::play_sound(const int &volume, const TextureFigure &texture)
{
    SDL2pp::Chunk &sound = get_chunk(texture);
    sound.SetVolume(volume);
    for (int i = 0; i < 8; i++)
    {
        if (mixer.IsChannelPlaying(i))
            continue;
        mixer.PlayChannel(i, sound);
        break;
    }
}

SoundBox::~SoundBox()
{
}
