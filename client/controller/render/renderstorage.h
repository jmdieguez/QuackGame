#include "scene.h"
#include "duck.h"
#include "item.h"
#include "projectiledrawer.h"
#include "mapdrawer.h"
#include "boxitem.h"

class RenderStorage
{
private:
    Duck duck;
    Scene scene;
    Item item;
    ProjectileDrawer projectile_drawer;
    MapDrawer map_drawer;
    BoxItem box_item;

public:
    explicit RenderStorage(SDL2pp::Renderer &renderer);
    Duck &get_duck();
    Scene &get_scene();
    Item &get_item();
    ProjectileDrawer &get_projectile_drawer();
    MapDrawer &get_map_drawer();
    BoxItem &get_box_item();
    ~RenderStorage();
};