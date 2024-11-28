#include "chunk.h"
#include "../../../common/texturefigure.h"

class MusicBox : protected Chunk
{
private:
    SDL2pp::Mixer &mixer;

public:
    explicit MusicBox(SDL2pp::Mixer &mixer);
    void play_sound(const TextureFigure &texture);
    ~MusicBox();
};
