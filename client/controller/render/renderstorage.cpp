#include "renderstorage.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

RenderStorage::RenderStorage(SDL2pp::Renderer &renderer) : duck(renderer), scene(renderer)
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

RenderStorage::~RenderStorage()
{
}
