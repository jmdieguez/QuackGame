#include "chunk.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Chunk::Chunk()
{
}

SDL2pp::Chunk &Chunk::get_chunk(SoundType type)
{
    SoundStorage &storage = SoundStorage::get_instance();
    std::shared_ptr<Sound> sound_created = storage.get_sound(type);
    return sound_created.get()->get_Sound();
}

Chunk::~Chunk()
{
}
