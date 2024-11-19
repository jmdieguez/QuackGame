#ifndef TEXTURE_FACTORY_H
#define TEXTURE_FACTORY_H

#include <memory>

#include "texture.h"
#include "../common/texturefigure.h"

class TextureFactory
{
private:
    std::string get_path(TextureFigure figure);

public:
    TextureFactory();
    std::shared_ptr<Texture> create_texture(SDL2pp::Renderer &renderer, TextureFigure figure);
    ~TextureFactory();
};

#endif // TEXTURE_FACTORY_H