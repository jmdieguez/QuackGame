#include "gunsizefactory.h"
#include "sizedefsguns.h"

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

Size GunSizeFactory::get_gun_size_to_texture(const TextureFigure &texture) const
{
    if (texture == TextureFigure::AKFigure)
        return Size(AK_WIDTH, AK_HEIGHT);
    else if (texture == TextureFigure::BananaFigure)
        return Size(BANANA_WIDTH, BANANA_HEIGHT);
    else if (texture == TextureFigure::CowboyPistolFigure)
        return Size(COWBOY_PISTOL_WIDTH, COWBOY_PISTOL_HEIGHT);
    else if (texture == TextureFigure::DuelingPistolFigure)
        return Size(DUELING_PISTOL_WIDTH, BANANA_HEIGHT);
    else if (texture == TextureFigure::GrenadeFigure)
        return Size(GRENADE_WIDTH, GRENADE_HEIGHT);
    else if (texture == TextureFigure::MagnumFigure)
        return Size(MAGNUM_WIDTH, MAGNUM_HEIGHT);
    else if (texture == TextureFigure::PewPewLaserFigure)
        return Size(PEW_PEW_LASER_WIDTH, PEW_PEW_LASER_HEIGHT);
    else if (texture == TextureFigure::ShotgunFigure)
        return Size(SHOTGUN_WIDTH, SHOTGUN_HEIGHT);
    else
        return Size(SNIPER_WIDTH, SNIPER_HEIGHT);
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

GunSizeFactory::GunSizeFactory()
{
}

Size GunSizeFactory::get_size(const TextureFigure &texture) const
{
    return get_gun_size_to_texture(texture);
}

GunSizeFactory::~GunSizeFactory()
{
}
