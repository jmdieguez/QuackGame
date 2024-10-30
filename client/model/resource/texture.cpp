#include "texture.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Texture::Texture(SDL2pp::Renderer &renderer, const std::string &path)
    : surface(path), texture(renderer, surface)
{
    SDL_SetColorKey(surface.Get(), SDL_TRUE, SDL_MapRGB(surface.Get()->format, 0xFF, 0, 0xFF));
}

SDL_Texture *Texture::get_texture() const
{
    return texture.Get();
}

Texture::~Texture() {}