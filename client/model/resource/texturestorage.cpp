#include "texturestorage.h"

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

TextureFigure TextureStorage::gun_type_to_texture(GunType gun)
{
    if (GunType::CowboyPistol == gun)
        return TextureFigure::CowboyPistol;
    else if (GunType::Magnum == gun)
        return TextureFigure::Magnum;
    else if (GunType::DuelingPistol == gun)
        return TextureFigure::DuelingPistol;
    else if (GunType::Shotgun == gun)
        return TextureFigure::Shotgun;
    else if (GunType::Sniper == gun)
        return TextureFigure::Sniper;
    return TextureFigure::CowboyPistol;
}

TextureFigure TextureStorage::projectile_type_to_texture(ProjectileType projectile)
{
    if (ProjectileType::CowboyBullet == projectile)
        return TextureFigure::CowboyBullet;
    return TextureFigure::CowboyBullet;
}

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

std::shared_ptr<Texture> TextureStorage::get_texture(SDL2pp::Renderer &renderer, GunType gun)
{
    TextureFigure figure = gun_type_to_texture(gun);
    if (textures_created.find(figure) == textures_created.end())
        textures_created[figure] = factory.create_texture(renderer, figure);
    return textures_created[figure];
}

std::shared_ptr<Texture> TextureStorage::get_texture(SDL2pp::Renderer &renderer, ProjectileType projectile)
{
    TextureFigure figure = projectile_type_to_texture(projectile);
    if (textures_created.find(figure) == textures_created.end())
        textures_created[figure] = factory.create_texture(renderer, figure);
    return textures_created[figure];
}

TextureStorage::~TextureStorage()
{
}
