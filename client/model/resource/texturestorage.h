#ifndef TEXTURE_STORAGE_H
#define TEXTURE_STORAGE_H

#include <map>
#include <memory>
#include "texturefactory.h"

class TextureStorage
{
private:
    TextureFactory factory;
    std::map<TextureFigure, std::shared_ptr<Texture>> textures_created;

public:
    static TextureStorage &get_instance();
    std::shared_ptr<Texture> get_texture(SDL2pp::Renderer &renderer, TextureFigure figure);
    ~TextureStorage();
};

#endif // TEXTURE_STORAGE_H