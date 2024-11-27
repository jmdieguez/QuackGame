#ifndef SCENE_H
#define SCENE_H

#include "renderer.h"
#include "../../../common/snapshots.h"

class Scene : protected Renderer
{
private:
public:
    explicit Scene(SDL2pp::Renderer &renderer);
    void render(CameraSnapshot &camera, float &scale_x, float &scale_y);
    void render();
    ~Scene();
};

#endif // SCENE_H