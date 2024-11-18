#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <SDL2pp/SDL2pp.hh>
#include "../../../common/texturefigure.h"

class Renderer
{
private:
protected:
    SDL2pp::Renderer &renderer;
    SDL2pp::Texture &get_texture(TextureFigure figure);

public:
    explicit Renderer(SDL2pp::Renderer &renderer);
    ~Renderer();
};

#endif // TEXTURE_LOADER_H