#ifndef SOUND_BOX_H
#define SOUND_BOX_H

#include "chunk.h"
#include "../../../common/texturefigure.h"

class SoundBox : protected Chunk
{
private:
    SDL2pp::Mixer &mixer;

public:
    explicit SoundBox(SDL2pp::Mixer &mixer);
    void play_sound(const int &volume, const TextureFigure &texture);
    ~SoundBox();
};

#endif // SOUND_BOX_H