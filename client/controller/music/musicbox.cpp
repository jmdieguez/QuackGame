#include "musicbox.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

MusicBox::MusicBox(SDL2pp::Mixer &mixer) : mixer(mixer)
{
}

void MusicBox::play_sound(SoundSnapshot &sound_snapshot)
{
    SDL2pp::Chunk &sound = get_chunk(sound_snapshot.sound);
    sound.SetVolume(1);
    mixer.PlayChannel(-1, sound);
}

MusicBox::~MusicBox()
{
}
