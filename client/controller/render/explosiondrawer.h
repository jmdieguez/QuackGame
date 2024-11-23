#ifndef EXPLOSION_DRAWER_H
#define EXPLOSION_DRAWER_H

#include "renderer.h"
#include "../../../common/snapshots.h"

class ExplosionDrawer : protected Renderer
{
private:
    void set_xy(int frame_ticks, int &src_x);

public:
    explicit ExplosionDrawer(SDL2pp::Renderer &renderer);
    void render(ExplosionSnapshot &explosion, int frame_ticks);
    ~ExplosionDrawer();
};

#endif // EXPLOSION_DRAWER_H
