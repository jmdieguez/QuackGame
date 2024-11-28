#ifndef CHUNK_H
#define CHUNK_H

#include <SDL2/SDL.h>
#include <SDL2pp/SDL.hh>
#include <SDL2pp/Mixer.hh>
#include <SDL2pp/Chunk.hh>
#include "../../model/resource/sound/soundstorage.h"

class Chunk
{
private:
public:
    Chunk();
    SDL2pp::Chunk &get_chunk(const TextureFigure &texture);
    ~Chunk();
};

#endif // CHUNK_H