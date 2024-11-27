#include "projectilesizefactory.h"
#include "sizedefsprojectiles.h"

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

Size ProjectileSizeFactory::texture_to_projectile_size(const TextureFigure &texture) const
{
    if (texture == TextureFigure::CowboyBullet)
        return Size(PROJECTILE_GUN_WIDTH, PROJECTILE_GUN_HEIGHT);
    if (texture == TextureFigure::LaserRifleBullet)
        return Size(PROJECTILE_GUN_WIDTH, PROJECTILE_GUN_HEIGHT);
    else
        return Size(PROJECTILE_GRENADE_WIDTH, PROJECTILE_GRENADE_HEIGHT);
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

ProjectileSizeFactory::ProjectileSizeFactory()
{
}

Size ProjectileSizeFactory::get_size(const TextureFigure &texture) const
{
    return texture_to_projectile_size(texture);
}

ProjectileSizeFactory::~ProjectileSizeFactory()
{
}
