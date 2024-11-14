#include "soundstorage.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

SoundStorage &SoundStorage::get_instance()
{
    static SoundStorage instance;
    return instance;
}

std::shared_ptr<Sound> SoundStorage::get_sound(SoundType sound)
{
    if (sounds_created.find(sound) == sounds_created.end())
        sounds_created[sound] = factory.create_texture(sound);
    return sounds_created[sound];
}

SoundStorage::~SoundStorage()
{
}
