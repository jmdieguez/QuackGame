#include "texturestorage.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

TextureStorage &TextureStorage::get_instance()
{
    static TextureStorage instance;
    return instance;
}

std::shared_ptr<Texture> TextureStorage::get_texture(SDL2pp::Renderer &renderer, TextureFigure figure)
{
    if (textures_created.find(figure) == textures_created.end())
        textures_created[figure] = factory.create_texture(renderer, figure);
    return textures_created[figure];
}

TextureStorage::~TextureStorage()
{
}
