#include "chunk.h"
#include "../../../common/snapshots.h"

class MusicBox : protected Chunk
{
private:
    SDL2pp::Mixer &mixer;

public:
    explicit MusicBox(SDL2pp::Mixer &mixer);
    void play_sound(SoundSnapshot &sound_snapshot);
    ~MusicBox();
};
