#include "soundstorage.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

SoundStorage &SoundStorage::get_instance()
{
    static SoundStorage instance;
    return instance;
}

std::shared_ptr<Sound> SoundStorage::get_sound(const TextureFigure &texture)
{
    if (sounds_created.find(texture) == sounds_created.end())
        sounds_created[texture] = factory.create_texture(texture);
    return sounds_created[texture];
}

SoundStorage::~SoundStorage()
{
}
