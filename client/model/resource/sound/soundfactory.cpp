#include "soundfactory.h"

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

std::string SoundFactory::get_path(SoundType sound)
{
    if (sound == SoundType::SHOOT)
        return SHOOT_SOUND_PATH;
    return SHOOT_SOUND_PATH;
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

SoundFactory::SoundFactory()
{
}

std::shared_ptr<Sound> SoundFactory::create_texture(SoundType sound)
{
    std::string path = get_path(sound);
    return std::make_shared<Sound>(path);
}

SoundFactory::~SoundFactory()
{
}
