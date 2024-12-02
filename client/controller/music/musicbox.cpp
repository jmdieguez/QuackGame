#include "musicbox.h"
#include "pathmusic.h"

void MusicBox::play_next()
{
}

MusicBox::MusicBox(SDL2pp::Mixer &mixer) : paths({MUSIC_ONE_PATH, MUSIC_TWO_PATH, MUSIC_THREE_PATH}),
                                           mixer(mixer), current_index(0)
{
}

void MusicBox::start(unsigned volume)
{
    if (Mix_PlayingMusic() == 1)
        return;
    current_music = std::make_unique<SDL2pp::Music>(paths[current_index]);
    Mix_VolumeMusic(volume);
    Mix_PlayMusic(current_music->Get(), 1);
    current_index = (current_index + 1) % paths.size();
}

MusicBox::~MusicBox()
{
}
