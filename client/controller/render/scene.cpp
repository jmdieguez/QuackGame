#include "scene.h"
#include "../../../ui/defs.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Scene::Scene(SDL2pp::Renderer &renderer) : Renderer(renderer)
{
}

void Scene::render()
{   
    SDL2pp::Texture &background_texture = get_texture(TextureFigure::Background);
    SDL_Rect src = {0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT};
    SDL_Rect dst = {0, 0, 
        static_cast<int>(DEFAULT_WINDOW_WIDTH * 1.5f), 
        static_cast<int>(DEFAULT_WINDOW_HEIGHT * 1.5f)
    };
    renderer.Copy(background_texture, src, dst);
}

void Scene::render(CameraSnapshot &camera, float &scale_x, float &scale_y)
{   
    SDL2pp::Texture &background_texture = get_texture(TextureFigure::Background);
    SDL_Rect src = {camera.x, camera.y, camera.width, camera.height};
    SDL_Rect dst = { 0, 0, 
        static_cast<int>(DEFAULT_WINDOW_WIDTH * scale_x * 1.5f), 
        static_cast<int>(DEFAULT_WINDOW_HEIGHT * scale_y * 1.5f)
    };
    renderer.Copy(background_texture, src, dst);
}

Scene::~Scene()
{
}
