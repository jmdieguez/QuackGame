#include "renderer.h"
#include "../../model/resource/texturestorage.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Renderer::Renderer(SDL2pp::Renderer &renderer) : renderer(renderer)
{
}

SDL2pp::Texture &Renderer::get_texture(TextureFigure figure)
{
    TextureStorage &storage = TextureStorage::get_instance();
    std::shared_ptr<Texture> texture_created = storage.get_texture(renderer, figure);
    return texture_created.get()->get_texture();
}

Renderer::~Renderer()
{
}
