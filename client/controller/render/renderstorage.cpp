#include "renderstorage.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

RenderStorage::RenderStorage(SDL2pp::Renderer &renderer) : duck(renderer), scene(renderer), item(renderer),
                                                           projectile_drawer(renderer), map_drawer(renderer),
                                                           box_item(renderer), explosion(renderer), armor(renderer)
{
}

Duck &RenderStorage::get_duck()
{
    return duck;
}

Scene &RenderStorage::get_scene()
{
    return scene;
}

Item &RenderStorage::get_item()
{
    return item;
}

Armor &RenderStorage::get_armor()
{
    return armor;
}

ProjectileDrawer &RenderStorage::get_projectile_drawer()
{
    return projectile_drawer;
}

MapDrawer &RenderStorage::get_map_drawer()
{
    return map_drawer;
}

BoxItem &RenderStorage::get_box_item()
{
    return box_item;
}

ExplosionDrawer &RenderStorage::get_explosion()
{
    return explosion;
}

RenderStorage::~RenderStorage()
{
}
