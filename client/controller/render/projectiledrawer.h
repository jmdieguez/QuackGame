#ifndef PROJECTILE_DRAWER_H
#define PROJECTILE_DRAWER_H

#include "renderer.h"
#include "size/projectile/projectilesizefactory.h"
#include "../../../common/snapshots.h"

class ProjectileDrawer : protected Renderer
{
private:
    ProjectileSizeFactory size_factory;

public:
    explicit ProjectileDrawer(SDL2pp::Renderer &renderer);
    void render(ProjectileSnapshot &projectile);
    ~ProjectileDrawer();
};

#endif // PROJECTILE_DRAWER_H