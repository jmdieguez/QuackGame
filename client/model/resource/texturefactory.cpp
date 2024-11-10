#include "texturefactory.h"
#include "path.h"

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

std::string TextureFactory::get_path(TextureFigure figure)
{
    if (TextureFigure::DUCK == figure)
        return DUCK_PATH;
    else if (TextureFigure::CowboyPistol == figure)
        return COWBOY_PISTOL_PATH;
    else if (TextureFigure::Magnum == figure)
        return MAGNUM_PATH;
    else if (TextureFigure::CowboyBullet == figure)
        return COWBOY_BULLET_PATH;
    else if (TextureFigure::DuelingPistol == figure)
        return DUELING_PISTOL_PATH;
    else if (TextureFigure::Shotgun == figure)
        return SHOTGUN_PATH;
    else if (TextureFigure::Sniper == figure)
        return SNIPER_PATH;
    else if (TextureFigure::AK == figure)
        return AK_PATH;
    else if (TextureFigure::PewPewLaser == figure)
        return PEW_PEW_LASER_PATH;
    else if (TextureFigure::Grenade == figure)
        return GRENADE_PATH;
    else if (TextureFigure::Box_T == figure)
        return BOX_PATH;
    else if (TextureFigure::Spawn_T == figure)
        return SPAWN_PATH;
    else if (TextureFigure::Helmet == figure)
        return HELMET_PATH;
    else if (TextureFigure::Chestplate == figure)
        return CHESTPLATE_PATH;
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
