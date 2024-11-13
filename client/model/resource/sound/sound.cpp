#include "sound.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Sound::Sound(const std::string &path) : sound(path)
{
}

SDL2pp::Chunk &Sound::get_Sound()
{
    return sound;
}

Sound::~Sound()
{
}
