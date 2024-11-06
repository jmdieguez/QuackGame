#ifndef TEXTURE_STORAGE_H
#define TEXTURE_STORAGE_H

#include <map>
#include <memory>
#include "texturefactory.h"
#include "../common/gun_type.h"
#include "../common/projectiletype.h"

class TextureStorage
{
private:
    TextureFactory factory;
    std::map<TextureFigure, std::shared_ptr<Texture>> textures_created;
    TextureFigure gun_type_to_texture(GunType gun);
    TextureFigure projectile_type_to_texture(ProjectileType projectile);

public:
    static TextureStorage &get_instance();
    std::shared_ptr<Texture> get_texture(SDL2pp::Renderer &renderer, TextureFigure figure);
    std::shared_ptr<Texture> get_texture(SDL2pp::Renderer &renderer, GunType gun);
    std::shared_ptr<Texture> get_texture(SDL2pp::Renderer &renderer, ProjectileType projectile);
    ~TextureStorage();
};

#endif // TEXTURE_STORAGE_H