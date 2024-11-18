#include "textureloader.h"
#include "../../model/resource/texturestorage.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

TextureLoader::TextureLoader()
{
}

SDL2pp::Texture &TextureLoader::get_texture(SDL2pp::Renderer &renderer, TextureFigure figure)
{
    TextureStorage &storage = TextureStorage::get_instance();
    std::shared_ptr<Texture> texture_created = storage.get_texture(renderer, figure);
    return texture_created.get()->get_texture();
}

TextureLoader::~TextureLoader()
{
}
