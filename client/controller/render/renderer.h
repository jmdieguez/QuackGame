#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include "../../../common/texturefigure.h"
#include <SDL2pp/SDL2pp.hh>

class Renderer
{
private:
protected:
    SDL2pp::Renderer &renderer;

public:
    Renderer(SDL2pp::Renderer &renderer);
    SDL2pp::Texture &get_texture(TextureFigure figure);
    ~Renderer();
};

#endif // TEXTURE_LOADER_H