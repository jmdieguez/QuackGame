#ifndef DUCK_CLIENT_H
#define DUCK_CLIENT_H

#include "renderer.h"
#include "../../../common/snapshots.h"

class Duck : protected Renderer
{
private:
    void set_xywh(const DuckSnapshot &duck, const int &frame_ticks, int &x, int &y, int &w, int &h);
    void set_xy(DuckSnapshot &duck, int frame_ticks, int &src_x, int &src_y);
    void render_helmet_chestplate(DuckSnapshot &duck);
    void render_weapon(DuckSnapshot &duck);
    void render_duck(DuckSnapshot &duck, int frame_ticks);

public:
    explicit Duck(SDL2pp::Renderer &renderer);
    void render(DuckSnapshot &duck, int frame_ticks);
    ~Duck();
};

#endif // DUCK_CLIENT_H