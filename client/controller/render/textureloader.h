#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include "../../../common/texturefigure.h"
#include <SDL2pp/SDL2pp.hh>

class TextureLoader
{
private:
public:
    TextureLoader();
    SDL2pp::Texture &get_texture(SDL2pp::Renderer &renderer, TextureFigure figure);
    ~TextureLoader();
};

#endif // TEXTURE_LOADER_H