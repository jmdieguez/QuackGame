#include "renderstorage.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

RenderStorage::RenderStorage(SDL2pp::Renderer &renderer) : duck(renderer), scene(renderer), item(renderer), box_item(renderer)
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

BoxItem &RenderStorage::get_box_item()
{
    return box_item;
}

RenderStorage::~RenderStorage()
{
}
