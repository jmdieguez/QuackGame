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
