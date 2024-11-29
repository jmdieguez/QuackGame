#include "soundfactory.h"
#include <iostream>

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

std::string SoundFactory::get_path(const TextureFigure &texture)
{
    if (texture == TextureFigure::CowboyBullet)
        return SHOOT_SOUND_PATH;
    if (texture == TextureFigure::ExplosionFigure)
        return EXPLOSION_SOUND_PATH;
    return SHOOT_SOUND_PATH;
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

SoundFactory::SoundFactory()
{
}

std::shared_ptr<Sound> SoundFactory::create_texture(const TextureFigure &sound)
{
    std::string path = get_path(sound);
    return std::make_shared<Sound>(path);
}

SoundFactory::~SoundFactory()
{
}
