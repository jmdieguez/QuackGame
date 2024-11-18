#include "scene.h"
#include "duck.h"

class RenderStorage
{
private:
    Duck duck;
    Scene scene;

public:
    explicit RenderStorage(SDL2pp::Renderer &renderer);
    Duck &get_duck();
    Scene &get_scene();
    ~RenderStorage();
};
