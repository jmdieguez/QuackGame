#ifndef SOUND_H
#define SOUND_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2pp/SDL.hh>
#include <SDL2pp/Mixer.hh>
#include <SDL2pp/Chunk.hh>

class Sound
{
private:
    SDL2pp::Chunk sound;

public:
    explicit Sound(const std::string &path);
    SDL2pp::Chunk &get_Sound();
    ~Sound();
};

#endif // Sound_H