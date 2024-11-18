#include "scene.h"
#include "duck.h"
#include "item.h"
#include "boxitem.h"

class RenderStorage
{
private:
    Duck duck;
    Scene scene;
    Item item;
    BoxItem box_item;

public:
    explicit RenderStorage(SDL2pp::Renderer &renderer);
    Duck &get_duck();
    Scene &get_scene();
    Item &get_item();
    BoxItem &get_box_item();
    ~RenderStorage();
};
