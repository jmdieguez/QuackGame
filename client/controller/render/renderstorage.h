#include "scene.h"
#include "duck.h"
#include "item.h"

class RenderStorage
{
private:
    Duck duck;
    Scene scene;
    Item item;

public:
    explicit RenderStorage(SDL2pp::Renderer &renderer);
    Duck &get_duck();
    Scene &get_scene();
    Item &get_item();
    ~RenderStorage();
};
