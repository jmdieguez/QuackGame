#include "scene.h"

#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Scene::Scene(SDL2pp::Renderer &renderer) : Renderer(renderer)
{
}

void Scene::render()
{
    SDL2pp::Texture &background_texture = get_texture(TextureFigure::Background);
    SDL_Rect src = {0, 0, background_texture.GetWidth(), background_texture.GetHeight()};
    SDL_Rect dst = {0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT};
    renderer.Copy(background_texture, src, dst);
}

Scene::~Scene()
{
}
