#ifndef EXPLOSION_DRAWER_H
#define EXPLOSION_DRAWER_H

#include "renderer.h"
#include "../../../common/snapshots.h"

class ExplosionDrawer : protected Renderer
{
private:
    void set_xywh(const int &frame_ticks, int &x, int &y, int &w, int &h);

public:
    explicit ExplosionDrawer(SDL2pp::Renderer &renderer);
    void render(ExplosionSnapshot &explosion, int frame_ticks);
    ~ExplosionDrawer();
};

#endif // EXPLOSION_DRAWER_H
