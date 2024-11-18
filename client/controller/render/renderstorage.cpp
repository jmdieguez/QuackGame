#include "renderstorage.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

RenderStorage::RenderStorage(SDL2pp::Renderer &renderer) : duck(renderer), scene(renderer), item(renderer)
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

RenderStorage::~RenderStorage()
{
}
