#include "texturefactory.h"
#include "path.h"

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

std::string TextureFactory::get_path(TextureFigure figure)
{
    if (TextureFigure::DUCK == figure)
        return DUCK_PATH;
    else if (TextureFigure::CowboyPistolFigure == figure)
        return COWBOY_PISTOL_PATH;
    else if (TextureFigure::MagnumFigure == figure)
        return MAGNUM_PATH;
    else if (TextureFigure::CowboyBullet == figure)
        return COWBOY_BULLET_PATH;
    else if (TextureFigure::DuelingPistolFigure == figure)
        return DUELING_PISTOL_PATH;
    else if (TextureFigure::ShotgunFigure == figure)
        return SHOTGUN_PATH;
    else if (TextureFigure::SniperFigure == figure)
        return SNIPER_PATH;
    else if (TextureFigure::AKFigure == figure)
        return AK_PATH;
    else if (TextureFigure::PewPewLaserFigure == figure)
        return PEW_PEW_LASER_PATH;
    else if (TextureFigure::GrenadeFigure == figure)
        return GRENADE_PATH;
    else if (TextureFigure::Box_T == figure)
        return BOX_PATH;
    else if (TextureFigure::Spawn_T == figure)
        return SPAWN_PATH;
    else if (TextureFigure::Helmet == figure)
        return HELMET_PATH;
    else if (TextureFigure::Chestplate == figure)
        return CHESTPLATE_PATH;
    else if (TextureFigure::Background == figure)
        return BACKGROUND_PATH;
    return DUCK_PATH;
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

TextureFactory::TextureFactory()
{
}

std::shared_ptr<Texture> TextureFactory::create_texture(SDL2pp::Renderer &renderer, TextureFigure figure)
{
    std::string path = get_path(figure);
    return std::make_shared<Texture>(renderer, path);
}

TextureFactory::~TextureFactory()
{
}
