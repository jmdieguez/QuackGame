#include "soundfactory.h"
#include <iostream>

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

std::string SoundFactory::get_path(const TextureFigure &texture)
{
    if (texture == TextureFigure::CowboyBullet)
        return SHOOT_SOUND_PATH;
    else if (texture == TextureFigure::ExplosionFigure)
        return EXPLOSION_SOUND_PATH;
    else if (texture == TextureFigure::LaserRifleBullet)
        return LASER_RIFLE_BULLET_SOUND_PATH;
    else
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
