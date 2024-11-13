#include "texturestorage.h"

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

TextureFigure TextureStorage::gun_type_to_texture(GunType gun)
{
    if (GunType::CowboyPistol == gun)
        return TextureFigure::CowboyPistolFigure;
    else if (GunType::Magnum == gun)
        return TextureFigure::MagnumFigure;
    else if (GunType::DuelingPistol == gun)
        return TextureFigure::DuelingPistolFigure;
    else if (GunType::Shotgun == gun)
        return TextureFigure::ShotgunFigure;
    else if (GunType::Sniper == gun)
        return TextureFigure::SniperFigure;
    else if (GunType::AK == gun)
        return TextureFigure::AKFigure;
    else if (GunType::PewPewLaser == gun)
        return TextureFigure::PewPewLaserFigure;
    else if (GunType::Grenade == gun)
        return TextureFigure::GrenadeFigure;
    return TextureFigure::CowboyPistolFigure;
}

TextureFigure TextureStorage::projectile_type_to_texture(ProjectileType projectile)
{
    if (ProjectileType::CowboyBullet == projectile)
        return TextureFigure::CowboyBullet;
    if (ProjectileType::Grenade == projectile)
        return TextureFigure::GrenadeFigure;
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
