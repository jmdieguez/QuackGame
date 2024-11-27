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
    void render(ExplosionSnapshot &explosion, int frame_ticks, 
                                 CameraSnapshot &camera, 
                                 float &scale_x, float &scale_y);
    ~ExplosionDrawer();
};

#endif // EXPLOSION_DRAWER_H
